#include <iostream>
#include <inslib.h>

using namespace std;

int main(int argc, char** argv)
{
    Session sess("2350410138.bff673b.6fb4c0204ff044dda643231a85b71701");
    cout << sess.getUsersSelf() << endl;
    cout << sess.getUsersSelfRecentMedia() << endl;
    //cout << sess.searchAreaRecentMedia(1, 1, 5000);
    //cout << sess.getMediaComments("1733142723563011958_4486674398");
    //cout << sess.getTagInfo("hotbabe");
    //cout << sess.getTagRecentMedia("beautiful");
    cout << "\n";
    return 0;
}

