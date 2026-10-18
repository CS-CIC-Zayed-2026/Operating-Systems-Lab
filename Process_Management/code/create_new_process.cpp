#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    fork();

    cout << "The Process PID: " << getpid() << endl;

    return 0;
}