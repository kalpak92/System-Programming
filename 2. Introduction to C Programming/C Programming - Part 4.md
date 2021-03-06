# Using External Libraries

[TOC]

## Symbols and libraries

- External libraries provide a wealth of functionality – example: C standard library
- Programs access libraries’ functions and variables via identifiers known as **symbols**
- Header file ->  ***declarations/prototypes mapped to symbols at compile time***
- Symbols -> ***linked to definitions in external libraries during linking***
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

- Why aren’t symbols listed for other declarations in stdio.h?
  - Compiler doesn’t bother creating symbols for unused function prototypes (saves space)

		at happens when we link?	

```shell
gcc -Wall hello.o -o hello
```

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

### Static linkage

- Functions, global variables must be allocated memory before use

- Can allocate at compile time (static) or at run time (shared)

- Advantages/disadvantages to both

- ***Symbols in same file, other .o files, or static libraries (archives, .a files)* – static linkage**

- ***Symbols in shared libraries (.so files)* – dynamic linkage**

- gcc links against shared libraries by default, can force static linkage using **-static flag**

- What happens if we statically link against the library?

  ```shell
  gcc -Wall -static hello.o -o hello
  ```

  Our executable now contains the symbol puts: .

  ```shell
  .
  .
  00000000004014c0 W puts
  .
  .
  .
  0000000000400304 T main
  .
  .
  .
  000000000046cd04 R msg
  .
  .
  .
  ```

  ​	’W’: linked to another defined symbol

- At link time, statically linked symbols added to executable

- Results in much larger executable file (static – 688K, dynamic – 10K)

- Resulting executable does not depend on locating external library files at run time

- To use newer version of library, have to recompile

### Dynamic linkage

- Dynamic linkage occurs at run-time
- During compile, linker just looks for symbol in external shared libraries
- Shared library symbols loaded as part of **program startup** (before main())
- Requires external library to define symbol exactly as expected from header file declaration
  - changing function in shared library can break your program
  - version information used to minimize this problem
  - reason why common libraries like libc rarely modify or remove functions, even broken ones like gets()

## Linking external libraries

- Programs linked against C standard library by default
- To link against library libnamespec.so or libnamespec.a, use compiler flag ***-lnamespec*** to link against library
- Library must be in library path (standard library directories + directories specified using ***-L directory*** compiler flag) 
- Use ***-static*** for force static linkage

### Loading shared libraries

- Shared library located during compile-time linkage, but needs to be located again during run-time loading.
- Shared libraries located at run-time using linker library ***ld.so***
- Whenever shared libraries on system change, need to run ***ldconfig*** to update links seen by ***ld.so***
- During loading, symbols in dynamic library are allocated memory and loaded from shared library file.

### Loading shared libraries on demand

- In Linux, can load symbols from shared libraries on demand using functions in dlfcn.h

- Open a shared library for loading: 

  ```c
  void ∗ dlopen(const char ∗file, int mode); 
  ```

  values for mode: combination of **RTLD_LAZY** (lazy loading of library), **RTLD_NOW** (load now), **RTLD_GLOBAL** (make symbols in library available to other libraries yet to be loaded), **RTLD_LOCAL** (symbols loaded are accessible only to your code)


- Get the address of a symbol loaded from the library: 

  ```c
  void ∗ dlsym(void ∗ handle, const char ∗ symbol_name); 
  ```

  handle from call to dlopen; returned address is pointer to variable or function identified by **symbol_name**


- Need to close shared library file handle after done with symbols in library: 

  ```c
  int dlclose(void ∗ handle);
  ```

  These functions are not part of C standard library; need to link against library ***libdl: -ldl*** compiler flag.

## Creating libraries

- Libraries contain C code like any other program.

- Static or shared libraries compiled from (un-linked) object files created using gcc.

- Compiling a static library: 

  - compile, but do not link source files:

    ```shell
    gcc -g -Wall -c infile.c -o outfile.o
    ```

  - collect compiled (unlinked) files into an archive:

    ```shell
    ar -rcs libname.a outfile1.o outfile2.o ...
    ```

- Compile and do not link files using `gcc`:

  ```shell
  gcc -g -Wall -fPIC -c infile.c -o outfile.o
  ```

- **-fPIC option**: create position-independent code, since code will be repositioned during loading

- Link files using ld to create a shared object (.so) file:

  ```shell
  ld -shared -soname libname.so -o libname.so.version -lc outfile1.o outfile2.o ...
  ```

- If necessary, add directory to LD_LIBRARY_PATH environment variable, so ld.so can find file when loading at run-time

- Configure ld.so for new (or changed) library:

  ```shell
  ldconfig -v
  ```

## Summary

- linking: binds symbols to addresses.
- static linkage: occurs at compile time (static libraries).
- dynamic linkage: occurs at run time (shared libraries).
- shared libraries:
  - **ld.so** - locates shared libraries 
  - **ldconfig** - updates links seen by ld.so
  - **dlopen()**, **dlsym()**, **dlclose()** - load shared libraries on demand.
- compiling static libraries: **gcc**, **ar**
- compiling shared libraries: **gcc**, **ldconfig**