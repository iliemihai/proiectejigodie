#include <iostream>
#include <inslib.h>

using namespace std;

int main(int argc, char** argv) {
    Session sess("");
    cout << sess.getUsersSelf();

    return 0;
}
