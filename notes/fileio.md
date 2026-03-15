# Chapter 4 — File I/O: The Universal I/O Model

# 1. Overview of the UNIX I/O Model

Linux uses a **universal I/O model**, meaning the same system calls operate on all types of files.

Supported file types include:

* regular files
* device files
* pipes
* sockets
* terminals
* FIFOs

All I/O operations are performed using the same set of system calls. 

Core system calls:

```
open()
read()
write()
close()
```

This design enables programs to operate on **any file-like object without modification**.

Example:

```
read() can read from:
    regular file
    keyboard
    pipe
    socket
```

Kernel translates requests into the appropriate **filesystem or device-driver operation**. 

---

# 2. File Descriptors

All I/O in Linux is performed using **file descriptors (FD)**.

Definition:

```
File Descriptor = small non-negative integer used to reference an open file
```

Each process has its **own descriptor table**.

Typical values:

| FD | Purpose         | POSIX name    |
| -- | --------------- | ------------- |
| 0  | standard input  | STDIN_FILENO  |
| 1  | standard output | STDOUT_FILENO |
| 2  | standard error  | STDERR_FILENO |

These descriptors are **opened automatically by the shell** before executing a program. 

Example:

```
0 → keyboard input
1 → terminal output
2 → terminal error
```

---

# 3. Core File I/O System Calls

The Linux I/O interface revolves around **four fundamental system calls**. 

---

## 3.1 open()

Opens a file and returns a file descriptor.

```
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode);
```

Return:

```
success → file descriptor
failure → -1
```

Key arguments:

```
pathname → file path
flags → access mode and options
mode → permissions if file created
```

Common flags:

```
O_RDONLY   read only
O_WRONLY   write only
O_RDWR     read and write
O_CREAT    create file
O_TRUNC    truncate file
O_APPEND   append writes
```

Example:

```
int fd = open("file.txt", O_RDONLY);
```

---

## 3.2 read()

Reads data from a file descriptor.

```
#include <unistd.h>

ssize_t read(int fd, void *buffer, size_t count);
```

Return:

```
>0 → number of bytes read
0  → end of file
-1 → error
```

Behavior:

* reads **up to count bytes**
* may read **less than requested**

Example:

```
char buf[1024];
read(fd, buf, 1024);
```

---

## 3.3 write()

Writes data to a file descriptor.

```
#include <unistd.h>

ssize_t write(int fd, const void *buffer, size_t count);
```

Return:

```
>0 → number of bytes written
-1 → error
```

Important:

```
write() may perform partial writes
```

Program must handle retry logic.

Example:

```
write(fd, buf, nbytes);
```

---

## 3.4 close()

Releases a file descriptor and kernel resources.

```
#include <unistd.h>

int close(int fd);
```

Return:

```
0  → success
-1 → error
```

Best practice:

```
if (close(fd) == -1)
    perror("close");
```

Leaving descriptors open causes **resource leaks**. 

---

# 4. The File Offset (File Pointer)

Each open file has an associated **file offset**.

Definition:

```
File offset = byte position where next read/write occurs
```

Behavior:

```
open()  → offset = 0
read()  → offset moves forward
write() → offset moves forward
```

Kernel maintains offset **per open file description**.

---

# 5. Changing File Offset: lseek()

Used for **random access in files**.

```
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

Return:

```
new file offset
-1 on error
```

`whence` values:

| Value    | Meaning               |
| -------- | --------------------- |
| SEEK_SET | from start of file    |
| SEEK_CUR | from current position |
| SEEK_END | from end of file      |

Example:

```
lseek(fd, 0, SEEK_SET);   // go to start
```

Get current position:

```
lseek(fd, 0, SEEK_CUR);
```

---

# 6. Sequential vs Random I/O

Linux files behave like **byte streams**.

Sequential I/O:

```
read → read → read
```

Random access:

```
lseek → read/write
```

Typical use cases:

```
databases → random access
log files → sequential writes
```

---

# 7. End-of-File (EOF)

UNIX does **not use a special EOF character**.

EOF detection:

```
read() returns 0
```

Example:

```
while ((n = read(fd, buf, size)) > 0)
    process(buf);
```

---

# 8. Universality of the I/O Model

Key UNIX philosophy:

```
Everything behaves like a file
```

Therefore:

```
read() works on
    files
    pipes
    sockets
    devices
```

Benefits:

```
simple API
portable programs
device abstraction
```

Kernel internally translates the I/O request to the correct subsystem. 

---

# 9. Example: Minimal cp Implementation

Typical use of the universal I/O interface:

```
open source file
open destination file
loop:
    read()
    write()
close files
```

Pseudo implementation:

```
while ((numRead = read(inFd, buf, BUF_SIZE)) > 0)
    write(outFd, buf, numRead);
```

---

# 10. Operations Outside the Universal I/O Model

Some device operations require special control.

System call:

```
#include <sys/ioctl.h>

int ioctl(int fd, int request, ...);
```

Used for:

```
device control
terminal configuration
network operations
driver specific commands
```

`ioctl()` is **device-specific and not fully standardized**.

---

# 11. Key Kernel Data Structures Behind File I/O

Linux maintains three important tables:

### 1. File Descriptor Table (per process)

Stores:

```
FD → pointer to open file description
FD flags
```

---

### 2. Open File Table (system-wide)

Stores:

```
file offset
status flags
access mode
inode pointer
```

---

### 3. i-node Table

Stores persistent file metadata:

```
file type
permissions
timestamps
file size
locks
```

Relationship:

```
Process FD table
      ↓
Open File Table
      ↓
inode
```



---

# 12. Important Design Principles

Linux file I/O design is based on:

```
1. everything is a byte stream
2. everything is accessed through file descriptors
3. same interface for all devices
4. kernel abstracts device details
```

---

# 13. Key Takeaways (Revision Notes)

Core system calls:

```
open()
read()
write()
close()
lseek()
ioctl()
```

Essential ideas:

```
file descriptor abstraction
universal I/O model
byte-stream interface
kernel managed file offset
```

Mental model:

```
process
   ↓
file descriptor
   ↓
open file description
   ↓
inode
```

This abstraction layer is **fundamental to understanding Linux system programming and kernel interfaces**.
