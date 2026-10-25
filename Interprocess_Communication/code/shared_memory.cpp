#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
using namespace std;
const int SIZE = (int)1e5; // 100000

struct shared_memory {
    int arr[SIZE];
    long long sum[2];
};

int main() {

    // Create shared memory
    shared_memory* shared = (shared_memory*) mmap(
        nullptr, // Address: Let the OS choose the virtual memory address.
        sizeof(shared_memory), // Length: Size of the memory region in bytes.
        PROT_READ | PROT_WRITE, // Protection: Allow reading and writing to the memory.
        MAP_SHARED | MAP_ANONYMOUS,
        // MAP_SHARED: Changes are visible to processes sharing this mapping.
        // MAP_ANONYMOUS: Memory is not backed by a regular file.
        -1, // File descriptor: Not used for anonymous mappings.
        0 // Offset: Not used for anonymous mappings; must be 0.
    );

    if (shared == MAP_FAILED) {
        perror("mmap");
        return 1;
    }


    for (int i = 0; i < SIZE; i++) {
        shared->arr[i] = i;
    }

    shared->sum[0] = 0;
    shared->sum[1] = 0;

    pid_t child1_pid = fork();

    if (child1_pid == 0) {
        cout << "Child process 1: " << getpid() << endl;
        long long sum = 0;
        for (int i = 0; i < SIZE / 2; i++) {
            sum += shared->arr[i];
        }

        shared->sum[0] = sum;
        cout << "Child 1 finished and sum: " << sum << endl;
        _exit(0);
    }

    pid_t child2_pid = fork();
    if (child2_pid == 0) {
        cout << "Child process 2: " << getpid() << endl;
        long long sum = 0;
        for (int i = SIZE / 2; i < SIZE ;i++) {
            sum += shared->arr[i];
        }
        shared->sum[1] = sum;
        cout << "Child 2 finished and sum: " << sum << endl;
        _exit(0);
    }

    wait(nullptr);
    // waitpid(child1_pid, nullptr, 0);
    // waitpid(child2_pid, nullptr, 0);

    cout << "Child 1 sum: " << shared->sum[0] << endl;
    cout << "Child 2 sum: " << shared->sum[1] << endl;

    cout << "Result: " << shared->sum[0] + shared->sum[1] << endl;
    munmap(shared->arr, sizeof(shared_memory));

}