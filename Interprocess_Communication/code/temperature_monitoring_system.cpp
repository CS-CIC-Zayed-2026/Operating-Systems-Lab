#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
using namespace std;

struct  shared_memory{
    float temperature;
    bool running;
    bool updated;
};

int main() {
    shared_memory* shared = (shared_memory*) mmap(
        nullptr,
        sizeof(shared_memory),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (shared == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {

        shared->temperature = 0;
        shared->updated = false;
        shared->running = true;

        cout << "==== Temperature Sensor ====" << endl;
        while (true) {
            cout << "Enter temperature (-1 to stop): ";
            float in;
            cin >> in;
            if (in == -1) {
                shared->running = false;
                break;
            }
            shared->temperature = in;
            shared->updated = true;
        }

        munmap(shared, sizeof(shared_memory));
        _exit(0);
    }


    cout << "==== Monitoring System ===" << endl;
    ofstream logfile("temperature_monitoring_system.txt");

    if (!logfile.is_open()) {
        cout << "Failed to open logfile." << endl;
        wait(nullptr);
        munmap(shared, sizeof(shared_memory));
        return 1;
    }

    while (shared->running) {
        if (shared->updated) {
            logfile << "Temperature: " << shared->temperature << " C" << endl;
            shared->updated = false;
        }
    }

    wait(nullptr);
    cout << "Monitor stopped." << endl;
    logfile.close();
    munmap(shared, sizeof(shared_memory));

    return 0;
}