# Introduction to System Programming

### 1. **Hello World! (system call style)**

```c
#include <unistd.h>

int main()
{
	write(1, "Hello\n", 6);
	write(1, "World\n", 6);
	return 0;
}
```

**Write a program that uses `write()` to print out "Hi! My name is `<Your Name>`".**

```c
#include <unistd.h>

int main(int argc, char const *argv[])
{
	write(1, "Hi! My name is Kalpak Seal\n", 27);
	return 0;
}
```

### 2. Standard Error Stream!

```c
#include <unistd.h>
#include <stdio.h>
//#define STDOUT_FILENO 1
//#define STDERR_FILENO 2

int main()
{
	int count;
	for (count = 5; count; count--)
	{
		write(STDOUT_FILENO, "Hello\n", 6);
		write(STDERR_FILENO, ".\n", 2);
	}

	return 0;
}
```

Write a function to print out a triangle of height `n`  to standard error.

- Your function should have the signature `void write_triangle(int n)` and should use `write()`.
- The triangle should look like this, for n = 3:

```
*
**
***
```

The code is:

```c
#include <unistd.h>

void write_triangle(int n)
{
	int count;
	for (count = 1; count <= n; count++)
	{
		for (int j = 1; j <= count; j++)
			write(1, "*", 1);

		write(1, "\n", 1);
	}

}

int main(int argc, char const *argv[])
{
	write_triangle(3);
	return 0;
}
```

### 3. Writing to files

We use `**open**` to create a file along with the necessary flags and preferred mode. Also don't forget to include the necessary header files.

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	mode_t mode = S_IRUSR | S_IWUSR;
	int fildes = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
	write(fildes, "Great!\n", 7);
	close(fildes);
	
	return 0;
}
```

Now, do this:

Take your program from "Hello, World!" modify it write to a file called 

```
hello_world.txt
```

- Make sure to to use correct flags and a correct mode for `open()` (`man 2 open` is your friend).

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	mode_t mode = S_IRUSR | S_IWUSR;

	int fildes = open("hello_world.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
	if (fildes == -1)
	{
		perror("Open Failed");
		exit(1);
	}
	write(fildes, "Hello World!\n", 13);
	close(fildes);
	return 0;
}
```

#### Difference between write() and printf()

 A system call is a call to a function that is not part of the application but is inside the kernel. The kernel is a software layer that provides you some basic functionalities to abstract the hardware to you. Roughly, the kernel is something that turns your hardware into software.

You always ultimately use `write()` to write anything on a peripheral whatever is the kind of device you write on. `write()` is designed to **only** write a sequence of bytes, that's all and nothing more. But as `write()` is considered too basic (you may want to write an integer in ten basis, or a float number in scientific notation, etc), different libraries are provided to you by different kind of programming environments to ease you.

For example, the C programming langage gives you `printf()` that lets you write data in many different formats. So, you can understand `printf()` as a function that convert your data into a formatted sequence of bytes and that calls `write()` to write those bytes onto the output. But C++ gives you `cout`; Java `System.out.println`, etc. Each of these functions ends to a call to `write()`.

One thing to know (important) is that such a system call is costly! it is not a simple function call because you need to call something that is outside of your own code and the system must ensure that you are not trying to do nasty things, etc. So it is very common in higher print-like function that some buffering is built-in; such that write is not always called, but your data are kept into some hidden structure and written only when it is really needed or necessary (buffer is full or you really want to see the result of your print).

This is exactly what happens when you manage your money. If many people gives you 5 bucks each, you won't go deposit each to the bank! You keep then on your wallet (this is the **print**) up to the point it is full or you don't want to kept them anymore. Then you go to the bank and make a big deposit (this is the **write**). And you know that putting 5 bucks to your wallet is much much faster than going to the bank and make the deposit. The bank is the kernel/OS.

