#include<iostream>
#include <unistd.h>
using namespace std;

int main() {
    cout << "====== Process ======" << endl;
    cout << "The Process PID: " << getpid() << endl;
    return 0;
}