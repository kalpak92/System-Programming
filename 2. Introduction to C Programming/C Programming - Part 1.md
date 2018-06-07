# C Programming: Introduction

## `hello world` in C

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

## Preprocessor macros

Preprocessor macros begin with # character 

​	`#include <stdio.h>`

`#define msg "hello, 6.087 students" `  -**defines msg as “hello, 6.087 students” throughout source file**

`#define` can take arguments and be treated like a function 

​	`#define add3(x,y,z) ((x)+(y)+(z))`

- parentheses ensure order of operations
- **compiler performs inline replacement**; not suitable for recursion
- `#undef` - Undefines a preprocessor macro

### Conditional preprocessor macros

- `#ifdef` - If this macro is defined
- `#ifndef` - If this macro is not defined
- `\#if` - Test if a compile time condition is true
- `\#else`- The alternative for #if
- `\#elif` - #else an #if in one statement
- `\#endif` - End preprocessor conditional

#### EXAMPLE PROGRAM FOR CONDITIONAL COMPILATION DIRECTIVES:

##### A) Example of #IFDEF, #ELSE AND #ENDIF IN C:

- “#ifdef” directive checks whether particular macro is defined or not. If it is defined, “If” clause statements are included in source file.
- Otherwise, “else” clause statements are included in source file for compilation and execution.

```c
#include <stdio.h>
#define RAJU 100
 
int main()
{
   #ifdef RAJU
   printf("RAJU is defined. So, this line will be added in " \
          "this C file\n");
   #else
   printf("RAJU is not defined\n");
   #endif
   return 0;
}
```

**OUTPUT:**

```shell
RAJU is defined. So, this line will be added in this C file
```

##### B) Example of **#IFNDEF AND #ENDIF IN C:**

- \#ifndef exactly acts as reverse as #ifdef directive. If particular macro is not defined, “If” clause statements are included in source file.
- Otherwise, else clause statements are included in source file for compilation and execution.

```c
#include <stdio.h>
#define RAJU 100
int main()
{
   #ifndef SELVA
   {
      printf("SELVA is not defined. So, now we are going to " \
             "define here\n");
      #define SELVA 300
   }
   #else
   printf("SELVA is already defined in the program”);
 
   #endif
   return 0;
 
}
```

**OUTPUT**:

```shell
SELVA is not defined. So, now we are going to define here
```

##### C) Example of #IF, #ELSE AND #ENDIF IN C**:**

- “If” clause statement is included in source file if given condition is true.
- Otherwise, else clause statement is included in source file for compilation and execution.

```c
#include <stdio.h>
#define a 100
int main()
{
   #if (a==100)
   printf("This line will be added in this C file since " \
          "a = 100\n");
   #else
   printf("This line will be added in this C file since " \
          "a is not equal to 100\n");
   #endif
   return 0;
}
```

**OUTPUT:**

```shell
This line will be added in this C file since a = 100
```

##### D) Example of #UNDEF IN C LANGUAGE:

This directive undefines existing macro in the program.

```c
#include <stdio.h>
 
#define height 100
void main()
{
   printf("First defined value for height    : %d\n",height);
   #undef height          // undefining variable
   #define height 600     // redefining the same for new value
   printf("value of height after undef & redefine:%d",height);
}
```

**OUTPUT**:

```shell
First defined value for height : 100
value of height after undef & redefine : 600
```

##### E) Example of PRAGMA IN C LANGUAGE:

Pragma is used to call a function before and after main function in a C program

```c
#include <stdio.h>
 
void function1( );
void function2( );
 
#pragma startup function1
#pragma exit function2
 
int main( )
{
   printf ( "\n Now we are in main function" ) ;
   return 0;
}
 
void function1( )
{
   printf("\nFunction1 is called before main function call");
}
 
void function2( )
{
   printf ( "\nFunction2 is called just before end of " \
            "main function" ) ;"
}
```

**OUTPUT**:

```shell
Function1 is called before main function call
Now we are in main function
Function2 is called just before end of main function
```

###### More on PRAGMA directive in C LANGUAGE:

| **Pragma command**                                           | **Description**                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| #Pragma                                                             startup<function_name_1> | This directive executes function named “function_name_1” before |
| #Pragma                                                                  exit<function_name_2> | This directive executes function named “function_name_2” just before termination of the program. |
| #pragma warn – rvl                                           | If function doesn’t return a value, then warnings are suppressed by this directive while compiling. |
| #pragma warn – par                                           | If function doesn’t use passed function parameter , then warnings are suppressed |
| #pragma warn – rch                                           | If a non reachable code is written inside a program, such warnings are suppressed by this directive. |

### Why do we use '`#include <stdio.h>`'?

We're lazy! We don't want to declare the `printf` function. It's already done for us inside the file '`stdio.h`'. The `#include` includes the text of the file as part of our file to be compiled.

Specifically, the `#include` directive takes the file `stdio.h` (which stands for **st**an**d**ard **i**nput and **o**utput) located somewhere in your operating system, copies the text, and substitutes it where the `#include` was.

- stdio.h – part of the C Standard Library
  - other important header files: ctype.h, math.h, stdlib.h, string.h, time.h
- Included files must be on include path 
  - -Idirectory with gcc: specify additional include directories
  - standard include directories assumed by default
- **include "stdio.h"** – searches ./ for stdio.h first

## Questions

Consider the statement:

```c
double ans = 18.0/squared(2+1); 
```

For each of the four versions of the function macro squared() below, write the corresponding value of ans.

```c
1. #define squared(x) x**x
Answer: 18.0/2 + 1 ∗ 2 + 1 = 9 + 2 + 1 = 12. 

2. #define squared(x) (x*x) 
Answer: 18.0/(2 + 1 ∗ 2 + 1) = 18/5 = 3.6.
    
3. #define squared(x) (x)*(x)
Answer: 18.0/(2 + 1) ∗ (2 + 1) = 6 ∗ 3 = 18.
    
4. #define squared(x) ((x)*(x))
Answer: 18.0/((2 + 1) ∗ (2 + 1)) = 18/9 = 2.
```


## The main() function

- main(): entry point for C program
- Simplest version: no inputs, outputs 0 when successful, and nonzero to signal some error 
  - **int main(void);**
- Two-argument form of main(): access command-line arguments 
  - **int main(int argc, char ∗∗argv);**

### Question

**Describe the difference between the literal values 7, "7", and ’7’.** 

- The first literal describes an integer of value 7. 
- The second describes a null-terminated string consisting of the character ’7’. 
- The third describes the character ’7’, whose value is its ASCII character code (55). 

## Console I/O

- **stdout, stdin**: console output and input streams
- **puts(string)**: print string to stdout
- **putchar(char)**: print character to stdout
- **char = getchar()**: return character from stdin
- **string = gets(string)**: read line from stdin into string


# Variables and Data Types

- A variable is as named link/reference to a value stored in the system’s memory or an expression that can be evaluated.
- The datatype of an object in memory determines the set of values it can have and what operations that can be performed on it.
- C is a weakly typed language. It allows implicit conversions as well as forced (potentially dangerous) casting.

### Data types and sizes

C has a small family of datatypes.

- Numeric (int, float, double)
- Character (char)
- User defined (struct,union)

|         | **signed**                      | **unsigned**                                    |
| ------- | ------------------------------- | ----------------------------------------------- |
| short   | **short int** x;**short**  y;   | **unsigned  short** x;**unsigned short int** y; |
| default | **int** x;                      | **unsigned  int** x;                            |
| long    | **long** x;                     | **unsigned  long** x;                           |
| float   | **float** x;                    | N/A                                             |
| double  | **double** x;                   | N/A                                             |
| char    | **char** x;  **signed char** x; | **unsigned  char** x                            |

- The unsigned version has roughly double the range of its signed counterparts.
- Signed and unsigned characters differ only when used in arithmetic expressions.

### Constants

Constants are literal/fixed values assigned to variables or used directly in expressions.

|    Datatype    |                      Example                      |                     Meaning                     |
| :------------: | :-----------------------------------------------: | :---------------------------------------------: |
|                |                    int i = 3;                     |                     Integer                     |
|                |                    long l = 3;                    |                  Long Integer                   |
|    Integer     |              unsigned long ul = 3UL;              |                  Unsigned long                  |
|                |                   int I = 0xA;                    |                   Hexadecimal                   |
|                |                   int I = 012;                    |                  Octal Number                   |
|                |                 float pi = 3.1459                 |                      float                      |
| Floating Point |                 float pi = 3.14F                  |                      float                      |
|                |         double pi=3.1415926535897932384L          |                     double                      |
|   Character    |               ‘A’  ‘\x41’  ‘\0101’                | Character  Specified in Hex  Specified in Octal |
|     String     |                   “Hello World”                   |                 String Literal                  |
|  Enumeration   | enum BOOL {No, Yes}  enum COLOR {R=1, G, B, Y=10} |              No=0, Yes=1  G=2, B=3              |

### Declarations

The general format for a declaration is	***type variable-name [=value]***.

#### Examples

- **char x;** /∗ uninitialized ∗/
- **char x=’A’;**/∗ intialized to ’A’∗/
- **char x=’A’,y=’B’;**/∗multiple variables initialized ∗/
- **char x=y=’Z’;**/∗multiple initializations ∗/

# Understanding Big and Little Endian Byte Order

- Problem: Computers speak different languages, like people.

   Some write data "left-to-right" and others "right-to-left".

  - A machine can read its own data just fine - problems happen when one computer stores data and a different type tries to read it.

- Solutions

  - Agree to a common format (i.e., all network traffic follows a single format), or
  - Always include a header that describes the format of the data. If the header appears backwards, it means data was stored in the other format and needs to be converted.


### Numbers Vs. Data

The most important concept is to recognize the difference between a number and the data that represents it.

A **number** is an abstract concept, such as a count of something. You have ten fingers. The idea of "ten" doesn't change, no matter what representation you use: ten, 10, diez (Spanish), ju (Japanese), 1010 (binary), X (Roman numeral)... these representations all point to the same concept of "ten".

Contrast this with data. **Data** is a physical concept, a raw sequence of bits and bytes stored on a computer. **Data has no inherent meaning** and must be interpreted by whoever is reading it.

Data is like human writing, which is simply marks on paper. There is no inherent meaning in these marks. If we see a line and a circle (like this: |O) we may interpret it to mean "ten".

But we assumed the marks referred to a number. They could have been the letters "IO", a moon of Jupiter. Or perhaps the Greek goddess. Or maybe an abbreviation for Input/Output. Or someone's initials. Or the number 2 in binary ("10"). The list of possibilities goes on.

The point is that a single piece of data (|O) can be interpreted in many ways, and the meaning is unclear until someone clarifies the intent of the author.

Computers face the same problem. They store data, not abstract concepts, and do so using a sequence of 1's and 0's. Later, they read back the 1's and 0's and try to recreate the abstract concept from the raw data. Depending on the assumptions made, the 1's and 0's can mean very different things.

Why does this problem happen? Well, there's no rule that all computers must use the same language, just like there's no rule all humans need to. Each type of computer is internally consistent (it can read back its own data), but there are no guarantees about how **another** type of computer will interpret the data it created.

**Basic concepts**

- Data (bits and bytes, or marks on paper) is meaningless; it must be interpreted to create an abstract concept, like a number.
- Like humans, computers have different ways to store the same abstract concept. (i.e., we have many ways to say "ten": ten, 10, diez, etc.)

### Storing Numbers As Data

Thankfully, most computers agree on a few basic data formats (this was not always the case). This gives us a common starting point which makes our lives a bit easier:

- A bit has two values (on or off, 1 or 0)
- A byte is a sequence of 8 bits
  - The "leftmost" bit in a byte is the biggest. So, the binary sequence 00001001 is the decimal number 9. 00001001 = (23 + 20 = 8 + 1 = 9).
  - Bits are numbered from right-to-left. Bit 0 is the rightmost and the smallest; bit 7 is leftmost and largest.

We can use these basic agreements as a building block to exchange data. If we store and read data one byte at a time, it will work on any computer. The concept of a byte is the same on all machines, and the idea of which byte is first, second, third (Byte 0, Byte 1, Byte 2...) is the same on all machines.

If computers agree on the order of every byte, what's the problem?

Well, this is fine for single-byte data, like ASCII text. However, a lot of data needs to be stored using multiple bytes, like integers or floating-point numbers. And there is no agreement on how these sequences should be stored.

### Byte Example

Consider a sequence of 4 bytes, named W X Y and Z - I avoided naming them A B C D because they are hex digits, which would be confusing. So, each byte has a value and is made up of 8 bits.

```latex
 Byte Name:    W       X       Y       Z
 Location:     0       1       2       3
 Value (hex):  0x12    0x34    0x56    0x78
```

For example, W is an entire byte, 0x12 in hex or 00010010 in binary. If W were to be interpreted as a number, it would be "18" in decimal (by the way, there's nothing saying we have to interpret it as a number - it could be an ASCII character or something else entirely).

With me so far? We have 4 bytes, W X Y and Z, each with a different value.

### Understanding Pointers

Pointers are a key part of programming, especially the C programming language. A pointer is a number that references a memory location. It is up to us (the programmer) to interpret the data at that location.

In C, when you cast a pointer to certain type (such as a char * or int *), it tells the computer how to interpret the data at that location. For example, let's declare

```c
void *p = 0; // p is a pointer to an unknown data type
             // p is a NULL pointer -- do not dereference
char *c;     // c is a pointer to a char, usually a single byte
```

Note that we can't get the data from p because we don't know its type. p could be pointing at a single number, a letter, the start of a string, your horoscope, an image -- we just don't know how many bytes to read, or how to interpret what's there.

Now, suppose we write

```c
c = (char *)p;
```

Ah -- now this statement tells the computer to point to the same place as p, and interpret the data as a single character (`char` is typically a single byte, use `uint8_t` if not true on your machine). In this case, c would point to memory location 0, or byte W. If we printed c, we'd get the value in W, which is hex 0x12 (remember that W is a whole byte).

This example does not depend on the type of computer we have -- again, all computers agree on what a single byte is (in the past this was not the case).

The example is helpful, even though it is the same on all computers -- if we have a pointer to a single byte (char *, a single byte), we can walk through memory, reading off a byte at a time. We can examine any memory location and the endian-ness of a computer won't matter -- every computer will give back the same information.

### So, What's The Problem?

Problems happen when computers try to read multiple bytes. Some data types contain multiple bytes, like long integers or floating-point numbers. A single byte has only 256 values, so can store 0 - 255.

Now problems start - when you read multi-byte data, where does the biggest byte appear?

- Big endian machine: Stores data **big-end first**. When looking at multiple bytes, the first byte (lowest address) is the biggest.
- Little endian machine: Stores data **little-end first**. When looking at multiple bytes, the first byte is **smallest**.

The naming makes sense, eh? Big-endian thinks the big-end is first. (By the way, the big-endian / little-endian naming comes from Gulliver's Travels, where the Lilliputans argue over whether to break eggs on the little-end or big-end. Sometimes computer debates are just as meaningful :-))

Again, endian-ness does not matter if you have a single byte. If you have one byte, it's the only data you read so there's only one way to interpret it (again, because computers agree on what a byte is).

Now suppose we have our 4 bytes (W X Y Z) stored the same way on a big-and little-endian machine. That is, memory location 0 is W on both machines, memory location 1 is X, etc.

We can create this arrangement by remembering that bytes are machine-independent. We can walk memory, one byte at a time, and set the values we need. This will work on any machine:

```c
c = 0;     // point to location 0 (won't work on a real machine!)
*c = 0x12; // Set W's value
c = 1;     // point to location 1
*c = 0x34; // Set X's value
...        // repeat for Y and Z; details left to reader
```

This code will work on any machine, and we have both set up with bytes W, X, Y and Z in locations 0, 1, 2 and 3.

### Interpreting Data

Now let's do an example with multi-byte data (finally!). Quick review: a "short int" is a 2-byte (16-bit) number, which can range from 0 - 65535 (if unsigned). Let's use it in an example:

```c
short *s; // pointer to a short int (2 bytes)
s = 0;    // point to location 0; *s is the value
```

So, s is a pointer to a short, and is now looking at byte location 0 (which has W). What happens when we read the value at s?

- Big endian machine: I think a short is two bytes, so I'll read them off: location s is address 0 (W, or 0x12) and location s + 1 is address 1 (X, or 0x34). Since the first byte is biggest (I'm big-endian!), the number must be 256 * byte 0 + byte 1, or 256*W + X, or 0x1234. 

  I multiplied the first byte by 256 (2^8) because I needed to shift it over 8 bits.

- Little endian machine: I don't know what Mr. Big Endian is smoking. Yeah, I agree a short is 2 bytes, and I'll read them off just like him: location s is 0x12, and location s + 1 is 0x34. But in my world, the first byte is the littlest! The value of the short is byte 0 + 256 * byte 1, or 256*X + W, or 0x3412.

Keep in mind that both machines start from location s and read memory going upwards. There is no confusion about what location 0 and location 1 mean. There is no confusion that a short is 2 bytes.

But do you see the problem? The big-endian machine thinks s = 0x1234 and the little-endian machine thinks s = 0x3412. The same exact data gives two different numbers. Probably not a good thing.

### Yet Another Example

Let's do another example with 4-byte integer for "fun":

```
int *i; // pointer to an int (4 bytes on 32-bit machine)
i = 0;  // points to location zero, so *i is the value there
```

Again we ask: what is the value at i?

- Big endian machine: An int is 4 bytes, and the first is the largest. I read 4 bytes (W X Y Z) and W is the largest. The number is 0x12345678.
- Little endian machine: Sure, an int is 4 bytes, but the first is smallest. I also read W X Y Z, but W belongs way in the back -- it's the littlest. The number is 0x78563412.

Same data, different results - not a good thing. 

## The NUXI Problem

Issues with byte order are sometimes called the NUXI problem: UNIX stored on a big-endian machine can show up as NUXI on a little-endian one.

Suppose we want to store 4 bytes (U, N, I and X) as two shorts: UN and IX. Each letter is a entire byte, like our WXYZ example above. To store the two shorts we would write:

```c
short *s; // pointer to set shorts
s = 0;    // point to location 0
*s = UN;  // store first short: U * 256 + N (fictional code)
s = 2;    // point to next location
*s = IX;  // store second short: I * 256 + X
```

This code is not specific to a machine. If we store "UN" on a machine and ask to read it back, it had better be "UN"! I don't care about endian issues, if we store a value on one machine and read it back on the same machine, it must be the same value.

However, if we look at memory one byte at a time (using our char * trick), the order could vary. On a big endian machine we see:

```latex
Byte:     U N I X
Location: 0 1 2 3
```

Which make sense. U is the biggest byte in "UN" and is stored first. The same goes for IX: I is the biggest, and stored first.

On a little-endian machine we would see:

```latex
Byte:     N U X I
Location: 0 1 2 3
```

And this makes sense also. "N" is the littlest byte in "UN" and is stored first. Again, even though the bytes are stored "backwards" in memory, the little-endian machine *knows* it is little endian, and interprets them correctly when reading the values back. Also, note that we can specify hex numbers such as x = 0x1234 on any machine. Even a little-endian machine knows what you mean when you write 0x1234, and won't force you to swap the values yourself (you specify the hex number to write, and it figures out the details and swaps the bytes in memory, under the covers. Tricky.).

This scenario is called the "NUXI" problem because byte sequence UNIX is interpreted as NUXI on the other type of machine. Again, this is only a problem if you exchange data -- each machine is internally consistent.

## Exchanging Data Between Endian Machines

Computers are connected - gone are the days when a machine only had to worry about reading its own data. Big and little-endian machines need to talk and get along. How do they do this?

### Solution 1: Use A Common Format

The easiest approach is to agree to a common format for sending data over the network. The standard network order is actually big-endian, but some people get uppity that little-endian didn't win... we'll just call it "network order".

To convert data to network order, machines call a function hton (host-to-network). On a big-endian machine this won't actually do anything, but we won't talk about that here (the little-endians might get mad).

But it is important to use hton before sending data, even if you are big-endian. Your program may be so popular it is compiled on different machines, and you want your code to be portable (don't you?).

Similarly, there is a function ntoh (network to host) used to read data off the network. You need this to make sure you are correctly interpreting the network data into the host's format. You need to know the type of data you are receiving to decode it properly, and the conversion functions are:

```c
 htons() - "Host to Network Short"
 htonl() - "Host to Network Long"
 ntohs() - "Network to Host Short"
 ntohl() - "Network to Host Long"
```

Remember that a single byte is a single byte, and order does not matter.

These functions are critical when doing low-level networking, such as verifying the checksums in IP packets. If you don't understand endian issues correctly your life will be painful - take my word on this one. Use the translation functions, and know why they are needed.

### Solution 2: Use A Byte Order Mark (BOM)

The other approach is to include a magic number, such as 0xFEFF, before every piece of data. If you read the magic number and it is 0xFEFF, it means the data is in the same format as your machine, and all is well.

If you read the magic number and it is 0xFFFE (it is backwards), it means the data was written in a format different from your own. You'll have to translate it.

A few points to note. First, the number isn't really magic, but programmers often use the term to describe the choice of an arbitrary number (the BOM could have been any sequence of different bytes). It's called a byte-order mark because it indicates the byte order the data was stored in.

Second, the BOM adds overhead to all data that is transmitted. Even if you are only sending 2 bytes of data, you need to include a 2-byte BOM. Ouch!

Unicode uses a BOM when storing multi-byte data (some Unicode character encodings can have 2, 3 or even 4-bytes per character). XML avoids this mess by storing data in UTF-8 by default, which stores Unicode information one byte at a time. And why is this cool?

(Repeated for the 56th time) "Because endian issues don't matter for single bytes".

Right you are.

Again, other problems can arise with BOM. What if you forget to include the BOM? Do you assume the data was sent in the same format as your own? Do you read the data and see if it looks "backwards" (whatever that means) and try to translate it? What if regular data includes the BOM by coincidence? These situations are not fun.

## Why Are There Endian Issues At All? Can't We Just Get Along?

Ah, what a philosophical question.

Each byte-order system has its advantages. Little-endian machines let you read the lowest-byte first, without reading the others. You can check whether a number is odd or even (last bit is 0) very easily, which is cool if you're into that kind of thing. Big-endian systems store data in memory the same way we humans think about data (left-to-right), which makes low-level debugging easier.

But why didn't everyone just agree to one system? Why do certain computers have to try and be different?

Let me answer a question with a question: Why doesn't everyone speak the same language? Why are some languages written left-to-right, and others right-to-left?

Sometimes communication systems develop independently, and later need to interact.

# Operators

## Arithmetic Operators

| operator |    meaning     |                           examples                           |
| :------: | :------------: | :----------------------------------------------------------: |
|    +     |    addition    |   x=3+2; /∗constants∗/ y+z; /∗variables∗/  x+y+2; /∗both∗/   |
|    -     |  subtraction   | 3−2; /∗constants∗/ int x=y−z; /∗variables∗/  y−2−z; /∗both∗/ |
|    *     | multiplication | int x=3∗2;  /∗constants∗/  int x=y∗z; /∗variables∗/  x∗y∗2;  /∗both∗/ |
|    /     |    division    | float  x=3/2; /∗produces x=1 (int /) ∗/ float x=3.0/2 /∗produces  x=1.5 (float /) ∗/ int x=3.0/2; /∗produces  x=1 (int conversion)∗/ |
|    %     |    modulus     | int  x=3%2; /∗produces x=1∗/ int y=7;int x=y%4; /∗produces  3∗/ int y=7;int x=y%10; /∗produces 7∗/  15 |

## Relational Operators

Relational operators compare two operands to produce a ’Boolean’ result. In C any non-zero value (1 by convention) is considered to be ’true’ and 0 is considered to be false.

| operator | meaning                  | examples                                               |
| -------- | ------------------------ | ------------------------------------------------------ |
| >        | greater than             | 3>2; /∗evaluates to 1 ∗/  2.99>3 /∗evaluates to 0 ∗/   |
| >=       | greater than or equal to | 3>=3; /∗evaluates to 1 ∗/  2.99>=3 /∗evaluates to 0 ∗/ |
| <        | lesser than              | 3<3; /∗evaluates to 0 ∗/  ’A’<’B’/∗evaluates to 1∗/    |
| <=       | lesser than or equal to  | 3<=3; /∗evaluates to 1 ∗/  3.99<3 /∗evaluates to 0 ∗/  |

Testing equality is one of the most commonly used relational operator.

| operator |   meaning    |                        examples                        |
| :------: | :----------: | :----------------------------------------------------: |
|    ==    |   Equal to   | 3==3; /∗evaluates to 1 ∗/  ’A’==’a’/∗evaluates to 0 ∗/ |
|    !=    | Not equal to | 3!=3; /∗evaluates to 0 ∗/  2.99!=3 /∗evaluates to 1 ∗/ |

## Logical Operators

| operators | meaning |                           examples                           |
| :-------: | :-----: | :----------------------------------------------------------: |
|    &&     |   AND   | ((9/3)==3) && (2∗3==6); /∗evaluates to 1 ∗/ (’A’==’a’)  && (3==3) /∗evaluates to 0 ∗/ |
|   \|\|    |   OR    | 2==3 \|\| ’A’==’A’; /∗evaluates to 1 ∗/  2.99>=3 \|\| 0 /∗evaluates to 0 ∗/ |
|     !     |   NOT   | !(3==3); /∗evaluates to 0 ∗/ !(2.99>=3) /∗evaluates  to 1 ∗/ |

Short circuit: The evaluation of an expression is discontinued if the value of a conditional expression can be determined early. Be careful of any side effects in the code.
Examples:

- `(3==3) || ((c=getchar())==’y’)`

  The second expression is not evaluated.

- `(0) && ((x=x+1)>0)` 

  The second expression is not evaluated.

## Bitwise Operators

| operator |   meaning   |                           examples                           |
| :------: | :---------: | :----------------------------------------------------------: |
|    &     |     AND     | 0x77 & 0x3; /∗evaluates to 0x3 ∗/ 0x77 & 0x0;  /∗evaluates to 0 ∗/ |
|    \|    |     OR      | 0x700 \| 0x33; /∗evaluates to 0x733 ∗/ 0x070 \| 0 /∗evaluates to 0x070 ∗/ |
|    ˆ     |     XOR     | 0x770 ^ 0x773; /∗evaluates to 0x3 ∗/ 0x33 ^ 0x33; /∗evaluates to 0 ∗/ |
|    «     | left shift  |  0x01<<4; /∗evaluates to 0x10 ∗/ 1<<2; /∗evaluates to 4 ∗/   |
|    »     | right shift |  0x010>>4; /∗evaluates to 0x01 ∗/ 4>>1 /∗evaluates to 2 ∗/   |

Notes:

- AND is true only if both operands are true.
- OR is true if any operand is true.
- XOR is true if only one of the operand is true.

## Assignment Operators

Another common expression type found while programming in C is of the type

​		 **`var = var (op) expr`**

- x=x+1
- x=x∗10
- x=x/2

C provides compact assignment operators that can be used instead.

- x+=1 /∗is the same as x=x+1∗/
- x−=1 /∗is the same as x=x−1∗/
- x∗=10 /∗is the same as x=x∗10 ∗/
- x/=2 /∗ is the same as x=x/2
- x%=2 /∗is the same as x=x%2

## Conditional Expression

A common pattern in C (and in most programming) languages is the following: 

`if ( cond )` 

​	x=<expra >;
`else`
	`x=<exprb >;`

C provides syntactic sugar to express the same using the ternary operator ’**?**:’

| sign = x?0?1:-1      <br /><br />if (x>0)<br />      sign=1  <br />else<br />    sign=-1 | isodd = x%2==1 ? 1 : 0     <br /><br />if (x%2 ==1)<br />      isodd = 1  <br />else<br />      isodd=0 |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
|                                                              |                                                              |

Notice how the ternary operator makes the code shorter and easier to understand (syntactic sugar).

## Type Conversions

When variables are promoted to higher precision, data is preserved. This is automatically done by the compiler for mixed data type expressions. 

```c
int i;
float f;
f=i +3.14159; / ∗ i is promoted to float ,f=(float)i+3.14159 ∗ /
```

Another conversion done automatically by the compiler is ’char’ -> ’int’. This allows comparisons as well as manipulations of character variables. 

```c
isupper =(c>=’A’ && c<=’Z’)?1:0; / ∗c and literal constants are converted to int ∗ / 
if (! isupper ) 
c=c−’a’+’A’ ;/ ∗ subtraction is possible because of integer conversion ∗ / 
```

As a rule (with exceptions), the compiler promotes each term in an binary expression to the highest precision operand.

## Precedence and Order of Evaluation

- ++,–,(cast),sizeof have the highest priority
- *,/,% have higher priority than +,-
- ==,!= have higher priority than &&,||
- assignment operators have very low priority

Use () generously to avoid ambiguities or side effects associated with precendence of operators.

- y=x∗3+2 /∗same as y=(x∗3)+2∗/
- x!=0 && y==0 /∗same as (x!=0) && (y==0)∗/
- d= c>=’0’&& c<=’9’/∗same as d=(c>=’0’) && (c<=’9’)∗/



## Questions

1. Determine the size, minimum and maximum value followingdata types. 

   Please specify if your machine is 32 bit or 64 bits in theanswer.

   ​	char 

   ​	unsigned char 

   ​	short 

   ​	int 

   ​	unsigned int 

   ​	unsigned long 

   ​	float

   Hint: Use sizeof() operator,limits.h and float.h headerfiles

   Answer

   ```c
   #include <stdio.h>
   #include <limits.h>
   #include <float.h>
    
   int main() 
   {
    
   	printf("The number of bits in a byte %d\n", CHAR_BIT);
    
   	printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
   	printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
   	printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);
    
   	printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
   	printf("The maximum value of SHORT INT = %d\n", SHRT_MAX); 
    
   	printf("The minimum value of INT = %d\n", INT_MIN);
   	printf("The maximum value of INT = %d\n", INT_MAX);
    
   	printf("The minimum value of CHAR = %d\n", CHAR_MIN);
   	printf("The maximum value of CHAR = %d\n", CHAR_MAX);
    
   	printf("The minimum value of LONG = %ld\n", LONG_MIN);
   	printf("The maximum value of LONG = %ld\n", LONG_MAX);
    
      return 0;
   }
   ```

   On my 32-bit machine ( /usr/include/limits.h, /usr/include/float.h), the sizes and limits are as follows. Results may differ if you used a 64 bit machine.

|   Data Type   | size (bytes) |          min           |          max           |
| :-----------: | :----------: | :--------------------: | :--------------------: |
|     char      |      1       |    SCHAR_MIN (-128)    |    SCHAR_MAX (127)     |
| unsigned char |      1       |           0            |    UCHAR_MAX (255)     |
|     short     |      2       |   SHRT_MIN (-32768)    |    SHRT_MAX(32767)     |
|      int      |      4       | INT_MIN (-2147483648)  |  INT_MAX (2147483647)  |
| unsigned int  |      4       |           0            | UINT_MAX (4294967295)  |
| unsigned long |      4       |           0            | ULONG_MAX (4294967295) |
|     float     |      4       | FLT_MIN (1.175494e-38) | FLT_MAX (3.402823e+38) |

2. Write logical expressions that tests whether a given character variable c is 

   lower case letter 

   ​	(Answer: **c>=’a’&& c<=’z’**) 

   upper case letter 

   ​	(Answer: **c>=’A’&& c<=’Z’**) 

   digit 

   ​	(Answer: **c>=’0’&& c<=’9’**) 

   white space (includes space,tab,new line) 

   ​	(Answer: **c==’\n’||c==’\t’|| c==’’**)

3. Using precedence rules, evaluate the following expressions and determine the value of the variables (without running the code). Also rewrite them using parenthesis to make the order explicit.

    	​	(a) Assume (x=0xFF33,MASK=0xFF00). Expression: **c=x & MASK ==0;**

   ​	(b) Assume (x=10, y=2,z=2;). Expression: **z=y=x++ + ++y∗2;** 

   ​	(c) Assume (x=10, y=4,z=1;). Expression: **y>>= x&0x2&& z**;

   Answer: 

   (a) The operator precedence is ’==’>’&’>’=’. Thus,the expression is equivalent to c= (x & (MASK==0)). Therefore **x=0xFF33,c=0.**

   (b) The operator precedence is ’++’>’*’>’+’. Thus, theexpression is equivalent to z =(x++) + ((++y)∗2). Therefore **x=11,y=3,z=10+3∗2=16.**

   (c) The operator precedence is’&’>’&&’>’>>=’. Thus, the expression is equivalent toy>>= (x & 0x2) && z. Therefore **x=10,y=2,z=1**.

