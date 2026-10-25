#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
const int SIZE = (int)1e5; // 100000
int arr[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }


    pid_t pid = fork();
    if (pid == 0) {
        cout << "Child process: " << getpid() << endl;
        long long sum = 0;
        for (int i = 0; i < SIZE / 2; i++) {
            sum += arr[i];
        }
        cout << sum << endl;
        cout << "Child finished" << endl;
    } else if (pid > 0) {
        cout << "Parent process: " << getpid() << endl;
        long long sum = 0;
        for (int i = SIZE / 2; i < SIZE; i++) {
            sum += arr[i];
        }
        cout << sum << endl;
        cout << "Parent finished" << endl;

    }
}