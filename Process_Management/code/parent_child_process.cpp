#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void print() {
    for (int i = 0; i < 10; i++) {
        cout << i << endl;
        sleep(1);
    }
}

int main() {

    pid_t pid = fork();

    // child process
    if (pid == 0) {
        cout << "The child process was created." << endl;
        cout << "(Child) The Process PID: " << getpid() << endl;
        cout << "(Child) The parent process PID: " << getppid() << endl;
        print();
        return 0;
    }
    else if (pid > 0) { // Parent process
        cout << "(Parent) The parent Process" << endl;
        cout << "(Parent) The Process PID: " << getpid() << endl;
        cout << "The child Process PID: " << pid << endl;
        wait(NULL);
        cout << "Parent process finished" << endl;
    } else {
        cout << "The child process was not created." << endl;
        return 1;
    }
    return 0;
}
