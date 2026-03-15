# Linux System lab  — Learning Repository

This repository documents my journey of learning **Linux systems programming** while studying concepts from **The Linux Programming Interface (TLPI)** and related operating system resources.

The goal of this repository is to build a **strong foundation in Linux internals and POSIX system programming** by implementing small programs, experiments, and examples that demonstrate how user-space programs interact with the Linux kernel.

---

## Objective

The primary goal of this repository is to develop a deeper understanding of:

* How Linux user-space programs interact with the kernel
* POSIX system calls and APIs
* Process and memory management
* File I/O and filesystem interfaces
* Signals, pipes, and interprocess communication
* Linux process model and scheduling

Each concept is explored through **small focused programs written in C**.

---

## Topics Covered

This repository will gradually cover the following areas of Linux programming:

### File I/O

* File descriptors
* `open()`, `read()`, `write()`, `close()`
* File permissions and flags

### Process Management

* `fork()`
* `exec()`
* `wait()` / `waitpid()`
* Process lifecycle

### Memory Management

* Virtual memory concepts
* `mmap()`
* Heap vs stack behavior

### Signals

* Signal handling
* `sigaction`
* Signal masks

### Interprocess Communication (IPC)

* Pipes
* Named pipes
* Shared memory
* Message queues

### File System Interfaces

* Directory operations
* File metadata
* Links and symbolic links

---

## Repository Structure

```text
linux-programming-interface/
│
├── file-io/
│   ├── cat.c
│   ├── cp.c
│
├── process/
│   ├── fork_example.c
│   ├── exec_example.c
│
├── signals/
│   ├── signal_handler.c
│
├── ipc/
│   ├── pipe_example.c
│
└── notes/
    └── concept_notes.md
```

Each directory focuses on a **specific Linux programming concept**, containing example programs and notes.

---

## Build Instructions

Most programs can be compiled using **GCC**.

Example:

```bash
gcc program.c -o program
```

Run the program:

```bash
./program
```

---

## Why This Repository Exists

As someone interested in **Embedded Linux, system-level development, and kernel internals**, understanding Linux programming interfaces is essential.

This repository serves as:

* A structured learning log
* A collection of system programming experiments
* A reference for commonly used Linux APIs

---

## Technologies Used

* C programming language
* GCC
* Linux operating system
* POSIX APIs

---

## Learning Resources

Primary reference:

* *The Linux Programming Interface* by Michael Kerrisk

Additional topics are explored alongside operating systems and Linux documentation.

---

## Status

Active learning repository — new examples and experiments will be added as I progress through Linux systems programming concepts.

---
