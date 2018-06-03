# C Programming, Part 1: Introduction

## `hello world` in C?

```c
#include <stdio.h>
int main(void) { 
    printf("Hello World\n");
    return 0; 
}
```

## Compiling a program

- gcc (included with most Linux distributions): compiler
- .o extension
  - omitted for common programs like gcc

- Run gcc:
  - ***gcc -Wall infilename.c -o outfilename.o***

- ***-Wall*** enables most compiler warnings
- More complicated forms exist
  - multiple source files
  - auxiliary directories
  - optimization, linking
- Embed debugging info and disable optimization:
  - ***gcc -g -O0 -Wall infilename.c -o outfilename.o***

### A Brief History and Introduction to GCC

GCC, formerly for "*GNU C Compiler*", has grown over times to support many languages such as C (`gcc`), C++ (`g++`), Objective-C, Objective-C++, Java (`gcj`), Fortran (`gfortran`), Ada (`gnat`), Go (`gccgo`), OpenMP, Cilk Plus, and OpenAcc. It is now referred to as "*GNU Compiler Collection*". The mother site for GCC is <http://gcc.gnu.org/>. The current version is GCC 7.3, released on 2018-01-25.

GCC is a key component of so-called "*GNU Toolchain*", for developing applications and writing operating systems. The GNU Toolchain includes:

1. GNU Compiler Collection (GCC): a compiler suit that supports many languages, such as C/C++ and Objective-C/C++.
2. GNU Make: an automation tool for compiling and building applications.
3. GNU Binutils: a suit of binary utility tools, including linker and assembler.
4. GNU Debugger (GDB).
5. GNU Autotools: A build system including Autoconf, Autoheader, Automake and Libtool.
6. GNU Bison: a parser generator (similar to lex and yacc).

GCC is *portable* and run in many operating platforms. GCC (and GNU Toolchain) is currently available on all Unixes. They are also ported to Windows (by Cygwin, MinGW and MinGW-W64). GCC is also a *cross-compiler*, for producing executables on different platform.

#### Compile and Link Separately

The above command *compile* the source file into object file and `link` with other object files and system libraries into executable in one step. You may separate compile and link in two steps as follows:

```shell
// Compile-only with -c option
> g++ -c -Wall -g Hello.cpp
// Link object file(s) into an executable
> g++ -g -o Hello.exe Hello.o
```

The options are:

- `-c`: Compile into object file "`Hello.o`". By default, the object file has the same name as the source file with extension of "`.o`" (there is no need to specify `-o` option). No linking with other object files or libraries.
- Linking is performed when the input file are object files "`.o`" (instead of source file "`.cpp`" or "`.c`"). GCC uses a separate linker program (called `ld.exe`) to perform the linking.

### GCC Compilation Process

![img](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/images/GCC_CompilationProcess.png) 

GCC compiles a C/C++ program into executable in 4 steps as shown in the above diagram. For example, a "gcc -o hello.exe hello.c" is carried out as follows:

1. **Pre-processing**: via the GNU C Preprocessor (cpp.exe), which includes the headers (#include) and expands the macros (#define).

   ```shell
   cpp hello.c > hello.i
   ```

   The resultant intermediate file "hello.i" contains the expanded source code.

2. **Compilation**: The compiler compiles the pre-processed source code into assembly code for a specific processor.

   ```shell
   gcc -S hello.i
   ```

   The -S option specifies to produce assembly code, instead of object code. The resultant assembly file is "hello.s".

3. **Assembly**: The assembler (as.exe) converts the assembly code into machine code in the object file "hello.o".

   ```shell
   as -o hello.o hello.s
   ```

4. **Linker**: Finally, the linker (ld.exe) links the object code with the library code to produce an executable file "hello.exe".

   ```shell
   ld -o hello.exe hello.o ...libraries...
   ```

##### Verbose Mode (-v)

You can see the detailed compilation process by enabling `-v` (verbose) option. For example,

```shell
gcc -v -o hello.exe hello.c
```

##### Defining Macro (-D)

You can use the `-D*name*` option to define a macro, or `-D*name*=*value*` to define a macro with a value. The `*value*` should be enclosed in double quotes if it contains spaces.

### Headers (.h), Static Libraries (.lib, .a) and Shared Library (.dll, .so)

##### Static Library vs. Shared Library

A library is a collection of pre-compiled object files that can be linked into your programs via the linker. Examples are the system functions such as `printf()` and `sqrt()`.

There are two types of external libraries: *static library* and *shared library*.

1. A static library has file extension of "`.a`" (archive file) in Unix or "`.lib`" (library) in Windows. When your program is linked against a static library, the machine code of external functions used in your program is ***copied into the executable***. A static library can be created via the *archive* program "`ar.exe`".
2. A shared library has file extension of "`.so`" (shared objects) in Unix or "`.dll`" (dynamic link library) in Windows. When your program is linked against a shared library, only a small table is created in the executable. Before the executable starts running, the operating system loads the machine code needed for the external functions - a process known as *dynamic linking*. Dynamic linking makes executable files smaller and saves disk space, because one copy of a library can be shared between multiple programs. Furthermore, most operating systems allows one copy of a shared library in memory to be used by all running programs, thus, saving memory. The shared library codes can be upgraded without the need to recompile your program.

Because of the advantage of dynamic linking, GCC, by default, links to the shared library if it is available.

One can list the contents of a library via "`nm *filename*`".

##### Searching for Header Files and Libraries (-I, -L and -l)

When compiling the program, the *compiler* needs the *header files* to compile the source codes; the *linker* needs the *libraries* to resolve external references from other object files or libraries. The compiler and linker will not find the headers/libraries unless you set the appropriate options, which is not obvious for first-time user.

For each of the headers used in your source (via `#include` directives), the compiler searches the so-called *include-paths* for these headers. The include-paths are specified via `-I*dir*` option (or environment variable `CPATH`). Since the header's filename is known (e.g., `iostream.h`, `stdio.h`), the compiler only needs the directories.

The linker searches the so-called *library-paths* for libraries needed to link the program into an executable. The library-path is specified via `-L*dir*` option (uppercase `'L'` followed by the directory path) (or environment variable `LIBRARY_PATH`). In addition, you also have to specify the library name. In Unixes, the library `lib*xxx*.a` is specified via `-l*xxx*` option (lowercase letter `'l'`, without the prefix "`lib`" and `".a`" extension). In Windows, provide the full name such as `-lxxx.lib`. The linker needs to know both the directories as well as the library names. Hence, two options need to be specified.

##### Default Include-paths, Library-paths and Libraries

Try list the default include-paths in your system used by the "GNU C Preprocessor" via "`cpp -v`":

```shell
> cpp -v
......
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-pc-cygwin/6.4.0/include
 /usr/include
 /usr/lib/gcc/x86_64-pc-cygwin/6.4.0/../../../../lib/../include/w32api
```

##### Example : Linking with external libraries

A library is a collection of precompiled object files which can be linked into programs. The most common use of libraries is to provide system functions, such as the square root function `sqrt` found in the C math library.

Libraries are typically stored in special *archive files* with the extension `‘.a’`, referred to as *static libraries*. They are created from object files with a separate tool, the GNU archiver `ar`, and used by the linker to resolve references to functions at compile-time.

The standard system libraries are usually found in the directories `‘/usr/lib’` and `‘/lib’`. For example, the C math library is typically stored in the file `‘/usr/lib/libm.a’` on Unix-like systems. The corresponding prototype declarations for the functions in this library are given in the header file `‘/usr/include/math.h’`. The C standard library itself is stored in `‘/usr/lib/libc.a’` and contains functions specified in the ANSI/ISO C standard, such as ‘printf’---this library is linked by default for every C program.

Here is an example program which makes a call to the external function `sqrt` in the math library `‘libm.a’`:

```c
#include <math.h>
#include <stdio.h>

int
main (void)
{
  double x = sqrt (2.0);
  printf ("The square root of 2.0 is %f\n", x);
  return 0;
}
```

Trying to create an executable from this source file alone causes the compiler to give an error at the link stage:

```shell
$ gcc -Wall calc.c -o calc
/tmp/ccbR6Ojm.o: In function `main':
/tmp/ccbR6Ojm.o(.text+0x19): undefined reference 
  to `sqrt'
```

The problem is that the reference to the `sqrt` function cannot be resolved without the external math library `‘libm.a’`. The function `sqrt` is not defined in the program or the default library `‘libc.a’`, and the compiler does not link to the file `‘libm.a’` unless it is explicitly selected. Incidentally, the file mentioned in the error message`‘/tmp/ccbR60jm.o’` is a temporary object file created by the compiler from `‘calc.c’`, in order to carry out the linking process.

To enable the compiler to link the `sqrt` function to the main program `‘calc.c’` we need to supply the library `‘libm.a’`. One obvious but cumbersome way to do this is to specify it explicitly on the command line:

```shell
$ gcc -Wall calc.c /usr/lib/libm.a -o calc
```

The library `‘libm.a’` contains object files for all the mathematical functions, such as `sin`, `cos`, `exp`, `log` and `sqrt`. The linker searches through these to find the object file containing the `sqrt` function.

Once the object file for the `sqrt` function has been found, the main program can be linked and a complete executable produced:

```shell
$ ./calc 
The square root of 2.0 is 1.414214
```

The executable file includes the machine code for the main function and the machine code for the `sqrt` function, copied from the corresponding object file in the library `‘libm.a’`.

To avoid the need to specify long paths on the command line, the compiler provides a short-cut option ‘-l’ for linking against libraries. For example, the following command,

```shell
$ gcc -Wall calc.c -lm -o calc
```

is equivalent to the original command above using the full library name `‘/usr/lib/libm.a’`.

### GCC Environment Variables

GCC uses the following environment variables:

- `PATH`: For searching the executables and run-time shared libraries (`.dll`, `.so`).
- `CPATH`: For searching the *include-paths* for headers. It is searched after paths specified in `-I<*dir*>` options. `C_INCLUDE_PATH` and `CPLUS_INCLUDE_PATH` can be used to specify C and C++ headers if the particular language was indicated in pre-processing.
- `LIBRARY_PATH`: For searching *library-paths* for link libraries. It is searched after paths specified in -`L<*dir*>` options.

### Utilities for Examining the Compiled Files

For all the GNU utilities, you can use "`*command* --help`" to list the help menu; or "`man *command*`" to display the man pages.

##### "file" Utility - Determine File Type

The utility "`file`" can be used to display the type of object files and executable files. For example,

```shell
$ gcc -c hello.c
$ gcc -o hello.exe hello.o
 
$ file hello.c
hello.c: C source, ASCII text, with CRLF line terminators

$ file hello.o
hello.o: data
 
> file hello.exe
hello.exe: PE32 executable (console) x86-64, for MS Windows
```

##### "nm" Utility - List Symbol Table of Object Files

The utility "`nm`" lists symbol table of object files. For example,

```shell
$ nm hello.o
0000000000000000 b .bss
0000000000000000 d .data
0000000000000000 p .pdata
0000000000000000 r .rdata
0000000000000000 r .rdata$zzz
0000000000000000 t .text
0000000000000000 r .xdata
                 U __main
0000000000000000 T main
                 U puts

$ nm hello.exe | grep main
00000001004080cc I __imp___main
0000000100401120 T __main
00000001004010e0 T main
......
```

"nm" is commonly-used to check if a particular function is defined in an object file. A `'T'` in the second column indicates a function that is *defined*, while a `'U'` indicates a function which is *undefined* and should be resolved by the linker.

##### "ldd" Utility - List Dynamic-Link Libraries

The utility "`ldd`" examines an executable and displays a list of the shared libraries that it needs. For example,

```shell
> ldd hello.exe
ntdll.dll => /cygdrive/c/WINDOWS/SYSTEM32/ntdll.dll (0x7ff9ba3c0000)
KERNEL32.DLL => /cygdrive/c/WINDOWS/System32/KERNEL32.DLL (0x7ff9b9880000)
KERNELBASE.dll => /cygdrive/c/WINDOWS/System32/KERNELBASE.dll (0x7ff9b6a60000)
SYSFER.DLL => /cygdrive/c/WINDOWS/System32/SYSFER.DLL (0x6ec90000)
ADVAPI32.dll => /cygdrive/c/WINDOWS/System32/ADVAPI32.dll (0x7ff9b79a0000)
msvcrt.dll => /cygdrive/c/WINDOWS/System32/msvcrt.dll (0x7ff9b9100000)
sechost.dll => /cygdrive/c/WINDOWS/System32/sechost.dll (0x7ff9b9000000)
RPCRT4.dll => /cygdrive/c/WINDOWS/System32/RPCRT4.dll (0x7ff9b9700000)
cygwin1.dll => /usr/bin/cygwin1.dll (0x180040000)
```

### Options That Control Optimization

Without any optimization option, the compiler’s goal is to reduce the cost of compilation and to make debugging produce the expected results. Statements are independent: if you stop the program with a breakpoint between statements, you can then assign a new value to any variable or change the program counter to any other statement in the function and get exactly the results you expect from the source code.

Turning on optimization flags makes the compiler attempt to improve the performance and/or code size at the expense of compilation time and possibly the ability to debug the program.

The compiler performs optimization based on the knowledge it has of the program. Compiling multiple files at once to a single output file mode allows the compiler to use information gained from all of the files when compiling each of them.

Not all optimizations are controlled directly by a flag.

Most optimizations are only enabled if an -O level is set on the command line. Otherwise they are disabled, even if individual optimization flags are specified.

Depending on the target and how GCC was configured, a slightly different set of optimizations may be enabled at each -O level than those listed here. You can invoke GCC with `-Q --help=optimizers` to find out the exact set of optimizations that are enabled at each level.

For examples.

- `-O`

- `-O1`

  Optimize. Optimizing compilation takes somewhat more time, and a lot more memory for a large function.With -O, the compiler tries to reduce code size and execution time, without performing any optimizations that take a great deal of compilation time.

- `-O2`

  Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff. As compared to -O, this option increases both compilation time and the performance of the generated code.

- `-O3`

  Optimize yet more.

- `-O0`

  Reduce compilation time and make debugging produce the expected results. This is the default.

- `-Os`

  Optimize for size. -Os enables all -O2 optimizations that do not typically increase code size. It also performs further optimizations designed to reduce code size.

- `-Ofast`

  Disregard strict standards compliance. -Ofast enables all -O3 optimizations. It also enables optimizations that are not valid for all standard-compliant programs. It turns on -ffast-math and the Fortran-specific -fstack-arrays, unless -fmax-stack-var-size is specified, and -fno-protect-parens.

- `-Og`

  Optimize debugging experience. -Og enables optimizations that do not interfere with debugging. It should be the optimization level of choice for the standard edit-compile-debug cycle, offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.

  So, in conclusion,

  The gcc option `-O` enables different levels of optimization. Use `-O0` to disable them and use `-S` to output assembly. `-O3` is the highest level of optimization.

  Starting with gcc 4.8 the optimization level `-Og` is available. It enables optimizations that do not interfere with debugging and is the recommended default for the standard edit-compile-debug cycle.

  To change the dialect of the assembly to either intel or att use `-masm=intel` or `-masm=att`.

## Debugging

Some useful commands:

- **break linenumber** – create breakpoint at specified line
- **break file:linenumber** – create breakpoint at line in file
- **run** – run program
- **c** – continue execution
- **next** – execute next line 
- **step** – execute next line or step into function
- **quit** – quit gdb
- **print *expression*** – print current value of the specified expression
- **help *command*** – in-program help

## Comments

- Comments: /∗ this is a simple comment ∗/

- Can span multiple lines

  / ∗ This comment

  spans

  multiple lines ∗ /

- Completely ignored by compiler

- Can appear almost anywhere

## Why do we use '`#include <stdio.h>`'?

We're lazy! We don't want to declare the `printf` function. It's already done for us inside the file '`stdio.h`'. The `#include` includes the text of the file as part of our file to be compiled.

Specifically, the `#include` directive takes the file `stdio.h` (which stands for **st**an**d**ard **i**nput and **o**utput) located somewhere in your operating system, copies the text, and substitutes it where the `#include` was.

- stdio.h – part of the C Standard Library
  - other important header files: ctype.h, math.h, stdlib.h, string.h, time.h
- Included files must be on include path 
  - -Idirectory with gcc: specify additional include directories
  - standard include directories assumed by default

- **include "stdio.h"** – searches ./ for stdio.h first

