#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

using namespace std;
using namespace chrono;

void sequential() {
    cout << "Sequential" << endl;
    auto start = steady_clock::now();

    cout << "Downloading file..." << endl;
    sleep(3);
    cout << "Download completed!" << endl;

    cout << "Preparing report..." << endl;
    sleep(3);
    cout << "Report completed!" << endl;

    auto end = steady_clock::now();

    double elapsed = duration<double>(end - start).count();

    cout << "All tasks completed!" << endl;
    cout << "Total execution time: "
         << elapsed << " seconds" << endl;
}

void concurrent() {
    cout << "Concurrent" << endl;
    auto start = steady_clock::now();

    pid_t pid = fork();

    if (pid == 0) {
        // Child: download the file
        cout << "Child: Downloading file..." << endl;
        sleep(3);
        cout << "Child: Download completed!" << endl;
    }
    else if (pid > 0) {
        // Parent: prepare the report
        cout << "Parent: Preparing report..." << endl;
        sleep(3);
        cout << "Parent: Report completed!" << endl;

        wait(NULL);

        auto end = steady_clock::now();
        double elapsed =
            duration<double>(end - start).count();

        cout << "All tasks completed!" << endl;
        cout << "Total execution time: "
             << elapsed << " seconds" << endl;
    }
    else {
        cerr << "Failed to create process." << endl;
    }
}

int main() {

    sequential();
    concurrent();
    return 0;
}