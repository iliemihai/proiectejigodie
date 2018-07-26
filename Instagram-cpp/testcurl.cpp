#include <iostream>

#include <fstream>
#include <sstream>

#include <string>

#include <cstdlib>

#include <cstring>


#include <curl/curl.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

void make_soap_envelope(std::string& q);

extern "C" {
	size_t postdata_fcn(void *ptr, size_t size, size_t nmemb, void *stream);
	size_t recvdata_fcn(void *ptr, size_t size, size_t nmemb, void *stream);
	int debug_fcn(CURL *h, curl_infotype it, char *s, size_t sz, void *v);
}

// Post this using CURL's postdata_fcn
std::string xml = "<?xml version='1.0' encoding='UTF-8'?>"
	"<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\""
	" xmlns:xsi=\"http://www.w3.org/1999/XMLSchema-instance\""
	" xmlns:xsd=\"http://www.w3.org/1999/XMLSchema\">"
	"<SOAP-ENV:Body>"
	"<ns1:doGoogleSearch xmlns:ns1=\"urn:GoogleSearch\""
	" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
	"<key xsi:type=\"xsd:string\">1uLxMnpQFHIGgqomK6o82/ewswSPddlW</key>"
	"<q xsi:type=\"xsd:string\">GOOGLE_QUERY</q>"
	"<start xsi:type=\"xsd:int\">0</start>"
	"<maxResults xsi:type=\"xsd:int\">10</maxResults>"
	"<filter xsi:type=\"xsd:boolean\">true</filter>"
	"<restrict xsi:type=\"xsd:string\"></restrict>"
	"<safeSearch xsi:type=\"xsd:boolean\">false</safeSearch>"
	"<lr xsi:type=\"xsd:string\"></lr>"
	"<ie xsi:type=\"xsd:string\">latin1</ie>"
	"<oe xsi:type=\"xsd:string\">latin1</oe>"
	"</ns1:doGoogleSearch>"
	"</SOAP-ENV:Body>"
	"</SOAP-ENV:Envelope>";

// What we get back from CURL, used by CURL's recvdata_fcn
std::string results = "";


int main(int argc, char *argv[])

{
	std::cout << "Enter google query: ";
	
	std::string tmp;
	std::getline(std::cin, tmp);
	
	// This replaces GOOGLE_QUERY in xml with the real one
	make_soap_envelope(tmp);
	

	curl_global_init(CURL_GLOBAL_DEFAULT);

	CURL *curl_handle = curl_easy_init();

	

	if (curl_handle == NULL) {

		std::cerr << "Something went wrong with libcurl: "
			<< "curl_easy_init() == NULL"

			<< std::endl;

		return (-1);

	}

	

	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, TRUE);

	curl_easy_setopt(curl_handle, CURLOPT_HEADER, TRUE);
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api.google.com/search/beta2");
	curl_easy_setopt(curl_handle, CURLOPT_POST, TRUE);
	curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, postdata_fcn);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, recvdata_fcn);
	curl_easy_setopt(curl_handle, CURLOPT_DEBUGFUNCTION, debug_fcn);

	
	std::ostringstream oss;
	std::string content_length;
	oss << "Content-Length: " << xml.size();
	
	curl_slist *http_headers = NULL;
	http_headers = curl_slist_append(http_headers, "Content-Type: text/xml; charset=utf-8");
	http_headers = curl_slist_append(http_headers, oss.str().c_str());
	http_headers = curl_slist_append(http_headers, "SOAPAction: urn:GoogleSearchAction");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, http_headers);
	
	CURLcode rc = curl_easy_perform(curl_handle);
	
	if (rc != CURLE_OK) {
		
		std::cerr << "Error from CURL: " << curl_easy_strerror(rc) << std::endl;
		
		long stats;
		CURLcode hc = curl_easy_getinfo(curl_handle, CURLINFO_HTTP_CODE, &stats);
		
		if (hc == CURLE_OK) {
			std::cerr << "HTTP response code: " << stats << std::endl;
		}
		else {
			std::cerr << "Failed to retreive HTTP response code from curl:\n"
					<< curl_easy_strerror(hc) << std::endl;
		}
	}
	else {
		std::cout << "OK from CURL" << std::endl;
	}
	
	std::cout << "Want to see the data returned by Google? ";
	std::getline(std::cin, tmp);
	
	if (tmp == "yes" || tmp == "y") {
		std::cout << "*** RESULTS FROM GOOGLE:\n\n\n" << results
				<< "\n\n\n" << std::endl;
	}

	curl_slist_free_all(http_headers);

	curl_easy_cleanup(curl_handle);

	curl_global_cleanup();

	

	return (0);

}


void make_soap_envelope(std::string& q)
{
	std::string::size_type query_pos;

		

	query_pos = xml.find("GOOGLE_QUERY");

	

	if (query_pos == std::string::npos) {

		std::cerr << "Failed to find GOOGLE_QUERY in xml" << std::endl;

		return;

	}

	

	xml.erase(query_pos, strlen("GOOGLE_QUERY"));

	xml.insert(query_pos, q);
}

size_t postdata_fcn(void *ptr, size_t size, size_t nmemb, void *stream)
{
	if (xml.size() > size * nmemb)
		return 0;
	
	strncpy((char *)ptr, xml.c_str(), xml.size());
	
	return xml.size();
}

size_t recvdata_fcn(void *ptr, size_t size, size_t nmemb, void *stream)
{
	if (size * nmemb == 0) {
		return 0;		// No search results (or nothing left?)
	}
	
	// Add 1 for the NUL terminator
	char *received = new char[size * nmemb + 1];
	
	if (received == (char *)0L) {
		std::cerr << "Failed to allocate memory for received data"
				<< std::endl;
		return 0;
	}
	
	// Add NUL terminator, since CURL doesn't NUL terminate result string
	strncpy(received, (char *)ptr, size * nmemb);
	received[size * nmemb] = 0;
	
	results = results + received;
	delete[] received;
	
	return (size * nmemb);
}

int debug_fcn(CURL *h, curl_infotype it, char *s, size_t sz, void *v)
{
	// Not NUL terminated
	char *buff = new char[sz + 1];
	
	if (buff == (char *)0L) {
		std::cerr << "Failed to allocate memory in CURL debug_fcn callback"
				<< std::endl;
		abort();
	}
	
	strncpy(buff, s, sz);
	buff[sz] = 0;
	
	if (it == CURLINFO_TEXT) {
		std::cerr << "CURL info: " << buff << std::endl;
	}
	else if (it == CURLINFO_HEADER_IN) {
		std::cerr << "CURL HTTP Header In: " << buff << std::endl;
	}
	else if (it == CURLINFO_HEADER_OUT) {
		std::cerr << "CURL HTTP Header Out: " << buff << std::endl;
	}
	else if (it == CURLINFO_DATA_IN) {
		// Lots of data in, turn on if necessary
	}
	else if (it == CURLINFO_DATA_OUT) {
		// Lots of data out, turn on if necessary
	}
	else {
		// Any others?
	}
	
	delete[] buff;
	return 0;
}
