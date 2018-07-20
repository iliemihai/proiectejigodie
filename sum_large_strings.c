#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void swap (char* str1, char* str2)
{
    char* aux;
    aux = str1;
    str1 = str2;
    str2 = aux;
}

char* reverse(char* str)
{
    size_t l = strlen(str);
    char* rv = (char*) malloc((l+1)*sizeof(char));
    rv[l+1] = '\0';
    int i;
    for (i=0;i<l;i++)
        rv[i] = str[l-i-1];
    return rv;
}

void findSum(char* str1, char*str2)
{
    if (strlen(str1) > strlen(str2))
        swap(str1, str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    str1 = reverse(str1);
    str2 = reverse(str2);
    char* str = (char*)malloc((len1+len2)*sizeof(char*));

    int carry = 0;
    int i;
    for (i=0;i<len1;i++)
    {
        int a = str1[i] - '0';
        int b = str2[i] - '0';
        int sum = (a+b+carry);
        str[i] = sum%10 + '0';
        carry = sum/10;
    }

    for (i=len1;i<len2;i++)
    {
        int sum = (str2[i]-'0')+carry;
        str[i] = sum%10 + '0';
        carry = sum/10;
    }

    if (carry)
        str[len1+len2-1] = carry+'0';

    str = reverse(str);
    printf("%s\n", str);
    free(str);
}

int main(int argc, char** argv)
{
    //printf("%d\n", strlen("oaie"));

    char* str1 = argv[1];
    char* str2 = argv[2];
    findSum(str1, str2);
}
