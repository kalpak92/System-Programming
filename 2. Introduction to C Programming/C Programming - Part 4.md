# Using External Libraries

## Symbols and libraries

- External libraries provide a wealth of functionality – example: C standard library
- Programs access libraries’ functions and variables via identifiers known as symbols
- Header file declarations/prototypes mapped to symbols at compile time
- Symbols linked to definitions in external libraries during linking
- Our own program produces symbols, too

Consider the simple hello world program written below:

```c
#include <stdio .h>
const char msg[ ] = "Hello, world." ;
int main ( void ) 
{
	puts (msg);
	return 0;
}
```

What variables and functions are declared globally?
	msg, main(), puts(), others in stdio.h

Let’s compile, but not link, the file hello.c to create hello.o:

```shell
gcc -Wall -c hello.c -o hello.o
```

- -c: compile, but do not link hello.c; result will compile the code into machine instructions but not make the program executable
- addresses for lines of code and static and global variables not yet assigned
- need to perform link step on hello.o (using gcc or ld) to assign memory to each symbol
- linking resolves symbols defined elsewhere (like the C standard library) and makes the code executable

Look at the symbols in the compiled file hello.o:

```shell
$ nm symbolLinking.o
00000000 b .bss
00000000 d .data
00000000 r .eh_frame
00000000 r .rdata
00000000 r .rdata$zzz
00000000 t .text
         U ___main
00000000 T _main
00000000 R _msg
         U _puts

```

’T’ – (text) code; ’R’ – read-only memory; ’U’ - undefined symbol

- Addresses all zero before linking; symbols not allocated memory yet
- Undefined symbols are defined externally, resolved during linking

Why aren’t symbols listed for other declarations in stdio.h?

- Compiler doesn’t bother creating symbols for unused function prototypes (saves space)

What happens when we link?
	gcc -Wall hello.o -o hello

- Memory allocated for defined symbols

- Undefined symbols located in external libraries (like libc for C standard library)

Let’s look at the symbols now:

```shell
$ nm hello
(other default symbols)
.
.
0000000000400524 T main
000000000040062c R msg
U puts@@GLIBC_2.2.5
```

- Addresses for static (allocated at compile time) symbols
- Symbol `puts` located in shared library GLIBC_2.2.5 (GNU C standard library)
- Shared symbol `puts` not assigned memory until run time.

## Static and dynamic linkage

Link editors are commonly known as linkers. The compiler automatically invokes the linker as the last step in compiling a program. The linker inserts code (or maps in shared libraries) to resolve program library references, and/or combines object modules into an executable image suitable for loading into memory. On Unix-like systems, the linker is typically invoked with the `ld` command.

Static linking is the result of the linker ***copying all library routines used in the program into the executable image***. This may require more disk space and memory than dynamic linking, but is both ***faster and more portable***, since it does not require the presence of the library on the system where it is run.

Dynamic linking is accomplished by ***placing the name of a sharable library in the executable image***. Actual linking with the library routines does not occur until the image is run, when both the executable and the library are placed in memory. An advantage of dynamic linking is that multiple programs can share a single copy of the library.

- Functions, global variables must be allocated memory before use
- Can allocate at compile time (static) or at run time (shared)
- Advantages/disadvantages to both
- Symbols in same file, other .o files, or static libraries (archives, .a files) – static linkage
- Symbols in shared libraries (.so files) – dynamic linkage
- gcc links against shared libraries by default, can force static linkage using **-static flag**

