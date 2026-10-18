# Process

## What is the process

- A **process** is informally defined as a **running program**. 
- While a program on a disk is a passive, "lifeless" collection of instructions and static data, the operating system takes these bytes, loads them into memory, and brings them to life as an active process

## How a Process is Created

To transform an on-disk program into a running process, the operating system executes a specific sequence of initialization steps:

1- **Loading Code and Static Data:** The OS reads the executable file from persistent storage (disk or SSD) and places its code and static variables into the process's address space in memory. 

- Simple operating systems perform loading **eagerly** (all at once), whereas modern operating systems perform loading **lazily** (loading code or data blocks only when needed during execution)

2- **Allocating the Run-Time Stack:** The OS allocates memory for the stack and initializes it with function arguments

3- **Allocating the Heap:** The OS sets up memory space for dynamically allocated data requested at runtime

4- **I/O Initialization:** In UNIX-based systems, the OS initializes three default file descriptors by default: standard input (0), standard output (1), and standard error (2)

- File Descriptor (FD): A small integer used by a process to identify an open file or an input/output resource.
- Standard Input (stdin, FD 0): The default input channel through which a process receives data, usually from the keyboard.
- Standard Output (stdout, FD 1): The default output channel through which a process sends normal results, usually to the terminal.
- Standard Error (stderr, FD 2): The default output channel through which a process sends error messages, usually to the terminal.

5- **Entry Point Execution:** Finally, the OS transfers control of the CPU to the process by jumping to its entry point function, `main()`

## What Is a Parent Process and a Child Process?

A program can start another program. When this happens, the operating system represents the relationship between the processes as a parent-child relationship.

- **Parent process**: The process that creates another process.

- **Child process**: The process created by the parent process.

For example, when you open a terminal and start a program, the shell running inside the terminal can create a new process to execute that program.

The shell is the parent process, and the process executing the program is its child.

A parent process can create multiple child processes, and those children can create other processes. This forms a hierarchy of processes called a process tree.

## What Is a Process ID (PID)?

The operating system needs a way to identify and manage each running process.

Therefore, the kernel assigns each process a unique number called a Process ID (PID).

The PID allows the operating system to distinguish one process from another.

Each process also has a Parent Process ID (PPID), which identifies its parent process.

PIDs are often assigned in increasing order, but this is not guaranteed. Once a process terminates, its PID may eventually be reused.

Traditionally, the first user-space process has PID 1. On most modern Linux systems, this process is systemd.

## Foreground and Background Jobs in Linux

### Foreground Jobs

A foreground job is a job that runs in the foreground of the current terminal session.

When a command runs in the foreground:

- The shell waits for the job to finish before accepting another command.

- The job can receive input from the terminal.

- The user can interact with the job through the terminal, depending on the program.

- The user can usually interrupt it by pressing Ctrl + C.

Example

Run a command that waits for 10 seconds:
``` shell 
$ sleep 10
```

The command runs in the foreground.

During these 10 seconds, the shell does not display a new command prompt. When the command finishes, the prompt appears again.

### Background Jobs

A background job is a job that runs without keeping the shell waiting for it to finish.

To start a command in the background, add the & symbol at the end of the command.

Example
```shell 
$ sleep 100 &
```

The shell starts the command as a background job and returns the command prompt without waiting for the command to finish.

This allows the user to execute other commands while the background job continues running.


## Essential Commands for Process Management

### `ps` : Process Status

```shell
$ ps
```

- Used to display information about currently running processes on a Linux system. It provides a snapshot of the processes at the time the command is executed.

- This basic command will show processes associated with the current terminal session

### `top`: Real-time Process Monitoring

```shell
$ top
```
- an interactive tool that provides a real-time view of the system’s processes.
- It displays system resource usage, including CPU and memory, and allows users to manage processes directly from the interface.

### `jobs`: Managing Background Jobs

``` shell
$ jobs
```

- used to list the jobs that are running in the background or have been stopped in the current shell session.

### `kill` : Terminate process

```shell
$ kill PID
```

- used to send signals to running processes, most commonly to terminate them
- By default, it requests a process to close gracefully using its unique Process ID (PID).


## Code
- [Get PID](code/get_current_pid.cpp)
- [Create Process](code/create_new_process.cpp)
- [Parent and Child Process](code/parent_child_process.cpp)
- [Example of why using process](code/example.cpp)



