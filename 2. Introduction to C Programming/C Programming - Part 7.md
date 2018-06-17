# Multithreading and Concurrency

## Concurrency vs Parallelism

"Concurrency is about dealing with lots of things at once. Parallelism is about doing lots of things at once." - Rob Pike 

An analogy:

**Naive Solution:** Build one wall. Go back to the start point. Build the other wall. It is simple to see how this isn't efficient. You'll be carrying the bricks along with you till the end, and then move them back to the start point.

**Concurrency:** Lay down one column of bricks of one wall, and then move to the other wall. When two corresponding columns of the two walls are built, move to the next column. This is a lot more efficient, since by the time you reach the end, you will be done, and the effort of carrying the pile of bricks from one end back to the start, will not be required.

**Parallelism:** Hire another brick layer who works alongside you on the second wall, while you are working on the first wall. This is obviously the best model, since it essentially reduces time to lay the bricks by half. However, it does require an extra brick layer.

**Parallelism vs. Concurrency:** Both are models of multi-programming.

Concurrency is essentially when two tasks are being performed at the same time. This might mean that one is 'paused' for a short duration, while the other is being worked on. Importantly, a different task is begun before an ongoing task is completed. This makes it a multi-programming model.

Parallelism requires that at least two processes/tasks are actively being performed at a particular moment in time. As illustrated by the metaphor above, this means that you require at least two 'processors' or 'workers'.

**The number of tasks actively being completed/performed at any instance of time, is what differentiates the two models.**

### **Concurrency**

You are running an operating system, in which you can have independent drivers inside the kernel (mouse driver, keyboard driver, display driver, etc). Those are not necessarily being run in parallel. If you only have one processor, only one can be run at a time, and it will still be able to run without any problem.  

### **Parallelism** 

You want to convert a colored image to black and white. The job can be done by calculating each pixel's RGB value to average of its neighbors. Since you can divide the task to smaller subtask (for example, each core is responsible to calculate specific region of the image), you can run them in parallel with multi-core CPU/GPU. 

## Process

![1529228525374](C:\Users\kals9\AppData\Local\Temp\1529228525374.png)

Each process is allocated a unique number, process identifier (PID). It's an integer between 2 and 32,768. When a process is started, the numbers restart from 2, and the number 1 is typically reserved for the init process as shown in the above example. The process #1 manages other processes.When we run a program, the code that will be executed is stored in a disk file. In general, a linux process can't write to the memory area. The area is for holding the program code so that the code can be loaded into memory as read-only (so, it can be safely shared). 

The system libraries can also be shared. Therefore, there need be only one copy of printf() in memory, even if there are many programs calling it.When we run two programs, there are variables unique to each programs, unlike the shared libraries, these are in separate data space of each process, and usually can't be shared. In other words, a process has its own stack space, used for local variables. It also has its own environment variables which are maintained by each process. A process should also has its own program counter, a record of where it has gotten to in its execution.

### Types of Process

#### Parent Process

In the operating system Unix, every process except process 0 (the **swapper**) is created when another process executes the fork() system call. The process that invoked fork is the parent process and the newly-created process is the child process. Every process (except process 0) has one parent process, but can have many child processes.

The operating system kernel identifies each process by its process identifier. Process 0 is a special process that is created when the system boots; after forking a child process (process 1), process 0 becomes the swapper process (sometimes also known as the “idle task”). Process 1, known as init, is the ancestor of every other process in the system. 

#### Child Process

A child process in computing is a process created by another process (the parent process).

A child process inherits most of its attributes, such as open files, from its parent. In UNIX, a child process is in fact created (using fork) as a copy of the parent. The child process can then overlay itself with a different program (using exec) as required. 

Each process may create many child processes but will have at most one parent process; if a process does not have a parent this usually indicates that it was created directly by the kernel. In some systems, including UNIX based systems such as Linux, the very first process (called init) is started by the kernel at booting time and never terminates (see Linux startup process); other parentless processes may be launched to carry out various daemon tasks in userspace. Another way for a process to end up without a parent is if its parent dies, leaving an orphan process; but in this case it will shortly be adopted by init. 

System call fork() is used to create processes. The purpose of fork() is to create a new process, which becomes the child process of the caller. 

#### Orphan Process 

An orphan process is a computer process whose ***parent process has finished or terminated, though it remains running itself.***

In a Unix-like operating system any orphaned process will be ***immediately adopted by the special init system process***. This operation is called re-parenting and occurs automatically. Even though technically the process has the init process as its parent, it is still called an orphan process since the process that originally created it no longer exists.

A process can be orphaned unintentionally, such as when the parent process terminates or crashes. The process group mechanism in most Unix-like operation systems can be used to help protect against accidental orphaning, where in coordination with the user’s shell will try to terminate all the child processes with the **SIGHUP** process signal, rather than letting them continue to run as orphans. 

#### Daemon Process

In Unix and other multitasking computer operating systems, a daemon is a computer program that runs as a background process, rather than being under the direct control of an interactive user. Typically daemon names end with the letter d: for example, `syslogd` is the daemon that implements the system logging facility and `sshd` is a daemon that services incoming SSH connections. 

In a Unix environment, the parent process of a daemon is often, but not always, the init process. A daemon is usually created by a process forking a child process and then immediately exiting, thus causing init to adopt the child process.

Daemon process is a **process orphaned intentionally.** 

#### Zombie Process

On Unix and Unix-like computer operating systems, ***a zombie process or defunct process is a process that has completed execution but still has an entry in the process table***. This entry is still needed to allow the parent process to read its child’s exit status. The term zombie process derives from the common definition of zombie — an undead person. In the term’s metaphor, the child process has “died” but has not yet been “reaped”. Also, unlike normal processes, the kill command has no effect on a zombie process. 

A zombie process is not the same as an orphan process. An orphan process is a process that is still executing, but whose parent has died. They do not become zombie processes; instead, they are adopted by init (process ID 1), which waits on its children. 

## Process vs Thread

Both processes and threads are independent sequences of execution. The typical difference is that threads (of the same process) run in a shared memory space, while processes run in separate memory spaces. 

### Process

An instance of a program that is being executed in its **own** address space. In POSIX systems, each
process maintains its own heap, stack, registers, file descriptors etc.
Communication:

- Shared memory
- Network
- Pipes, Queues

### Thread 

A light weight process that shares its address space with others.In POSIX systems, each thread
maintains the bare essentials: registers, stack, signals.
Communication:

- shared address space.

The major differences between threads and processes are:

1. Threads share the address space of the process that created it; processes have their own address space.
2. Threads have direct access to the data segment of its process; processes have their own copy of the data segment of the parent process.
3. Threads can directly communicate with other threads of its process; processes must use interprocess communication to communicate with sibling processes.
4. Threads have almost no overhead; processes have considerable overhead.
5. New threads are easily created; new processes require duplication of the parent process.
6. Threads can exercise considerable control over threads of the same process; processes can only exercise control over child processes.
7. Changes to the main thread (cancellation, priority change, etc.) may affect the behavior of the other threads of the process; changes to the parent process do not affect child processes. 

## Multithreaded Concurrency

Serial execution

- All our programs so far has had a single thread of execution: main thread.
- Program exits when the main thread exits.

Multithreaded

- Program is organized as multiple and concurrent threads of execution.
- The main thread spawns multiple threads.
- The thread may communicate with one another.

- Advantages:
  - Improves performance
  - Improves responsiveness
  - Improves utilization
  - Less overhead compared to multiple processes

## Multithreaded programming

Even in C, multithread programming may be accomplished in several ways

- Pthreads: POSIX C library.
- OpenMPgit 
- Intel threading building blocks
- Cilk (from CSAIL!)
- Grand central despatch
- CUDA (GPU)
- OpenCL (GPU/CPU)

