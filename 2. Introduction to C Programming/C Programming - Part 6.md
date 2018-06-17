

# Dynamic memory allocation

- Memory allocated during runtime
- Request to map memory using **mmap()** function (in **<sys/mman.h>**)
- Virtual memory can be returned to OS using **munmap()**
- Virtual memory either backed by a file/device or by demand-zero memory:
  - all bits initialized to zero
  - not stored on disk
  - used for stack, heap, uninitialized (at compile time) globals

## Mapping memory

**void ∗mmap( void ∗ start , size _t length , int prot , int flags , int fd , off _t offset );**

- asks OS to map virtual memory of specified length, using specified physical memory (file or demand-zero)
- fd is file descriptor (integer referring to a file, not a file stream) for physical memory (i.e. file) to load into memory
- for demand-zero, including the heap, use `MMAP_ANON` flag
- start – suggested starting address of mapped memory, usually NULL

## Unmap memory

**int munmap(void ∗start, size_t length);**

## The heap

- Heap – private section of virtual memory (demand-zero) used for dynamic allocation

- Starts empty, zero-sized

- **brk** – OS pointer to top of heap, moves upwards as heap grows

- To resize heap, can use **sbrk()** function:

  ```c
  void ∗sbrk(int inc); /∗ returns old value of brk_ptr ∗/
  ```

- Functions like **malloc() and new** (in C++) manage heap, mapping memory as needed

- Dynamic memory allocators divide heap into blocks

# Memory Layout of C programs

A typical memory representation of C program consists of following sections.

- Text segment
- Initialized data segment
- Uninitialized data segment
- Stack
- Heap 

![1529139776670](https://github.com/kalpak92/System-Programming/blob/master/2.%20Introduction%20to%20C%20Programming/Memory%20Layout.png)

### 1. Text Segment

A text segment, also known as a code segment or simply as text, is one of the sections of a program in an object file or in memory, which contains **executable instructions**. As a memory region, a text segment may be placed below the heap or stack in order to prevent heaps and stack overflows from overwriting it. Usually, ***the text segment is sharable so that only a single copy needs to be in memory for frequently executed programs,*** such as text editors, the C compiler, the shells, and so on. Also, the text segment is often **read-only**, to prevent a program from accidentally modifying its instructions. 

### 2. Initialized Data Segment

Initialized data segment, usually called simply the Data Segment. A data segment is a portion of virtual address space of a program, which contains the **global variables and static variables that are initialized by the programmer**. Note that, data segment is not read-only, since the values of the variables can be altered at run time. This segment can be further classified into 

- initialized read-only area
- initialized read-write area

For instance the global string defined by char s[] = “hello world” in C and a C statement like int debug=1 outside the main (i.e. global) would be stored in initialized read-write area. 

And a global C statement like `const char* string = “hello world”` makes the string literal “hello world” to be stored in initialized read-only area and the character pointer variable string in initialized read-write area. Ex: static int i = 10 will be stored in data segment and global int i = 10 will also be stored in data segment.

### 3. Uninitialized Data Segment

Uninitialized data segment, often called the “bss” segment, named after an ancient assembler operator that stood for “***block started by symbol.***” Data in this segment is initialized by the kernel to arithmetic 0 before the program starts executing. Uninitialized data starts at the end of the data segment and contains all **global variables and static variables that are initialized to zero or do not have explicit initialization in source code.** 

For instance a variable declared static int i; would be contained in the BSS segment.For instance a global variable declared int j; would be contained in the BSS segment. 

### 4. Stack

The stack area traditionally adjoined the heap area and grows the opposite direction; when the stack pointer met the heap pointer, free memory was exhausted. (With modern large address spaces and virtual memory techniques they may be placed almost anywhere, but they still typically grow opposite directions.)

The stack area contains the program stack, a LIFO structure, typically located in the higher parts of memory. On the standard PC x86 computer architecture it grows toward address zero; on some other architectures it grows the opposite direction. A “stack pointer” register tracks the top of the stack; it is adjusted each time a value is “pushed” onto the stack. The set of values pushed for one function call is termed a “stack frame”; a stack frame consists at minimum of a return address.

Stack, where automatic variables are stored, along with information that is saved each time a function is called. Each time a function is called, the address of where to return to and certain information about the caller’s environment, such as some of the machine registers, are saved on the stack. The newly called function then allocates room on the stack for its automatic and temporary variables. This is how recursive functions in C can work. Each time a recursive function calls itself, a new stack frame is used, so one set of variables doesn’t interfere with the variables from another instance of the function. 

### 5. Heap

Heap is the segment where dynamic memory allocation usually takes place.The heap area begins at the end of the BSS segment and grows to larger addresses from there. ***The Heap area is managed by malloc, realloc, and free, which may use the brk and sbrk system calls to adjust its size (note that the use of brk/sbrk and a single “heap area” is not required to fulfill the contract of malloc/realloc/free; they may also be implemented using mmap to reserve potentially non-contiguous regions of virtual memory into the process’ virtual address space).*** The Heap area is shared by all shared libraries and dynamically loaded modules in a process. 

### `size` command

The size(1) command reports the sizes (in bytes) of the text, data, and bss segments. The GNU size utility lists the section sizes---and the total size---for each of the object or archive files objfile in its argument list. By default, one line of output is generated for each object file or each module in an archive.objfile... are the object files to be examined. If none are specified, the file "a.out" will be used. 

### Examples

```c
#include <stdio.h>
 
int main(void)
{
    return0;
}
```

```shell
gcc memory-layout.c -o memory-layout

size memory-layout

text       data        bssdec        hex    filename

960        248          8       1216        4c0    memory-layout
```

Let us add one global variable in program, now check the size of bss. 

```c
#include <stdio.h>
 
int global; /* Uninitialized variable stored in bss*/
 
int main(void)
{
    return0;
}
```

```shell
gcc memory-layout.c -o memory-layout

size memory-layout

text       data        bssdec        hex    filename

 960        248         12       1220        4c4    memory-layout
```



# C - Memory Management

Although C inherently does not have any technique to allocate memory dynamically, there are 4 library functions defined under `<stdlib.h>` for dynamic memory allocation. 

| Sr.No. | Function & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **void \*calloc(int num, int size);**<br />This function allocates an array of **num** elements each of which size in bytes will be **size**. |
|   2    | **void free(void \*address);**<br />This function releases a block of memory block specified by address. |
|   3    | **void \*malloc(int num);**<br />This function allocates an array of **num** bytes and leave them uninitialized. |
|   4    | **void \*realloc(void *address, int newsize);**<br />This function re-allocates memory extending it upto newsize. |

## malloc()

he name malloc stands for "memory allocation".

The function `malloc()` reserves a block of memory of specified size and return a [pointer](https://www.programiz.com/c-programming/c-pointers) of type `void` which can be casted into pointer of any form.

### Syntax of malloc()

```c
ptr = (cast-type*) malloc(byte-size)
```

Here, ptr is pointer of cast-type. The `malloc()` function returns a pointer to an area of memory with size of byte size. If the space is insufficient, allocation fails and returns NULL pointer.

```c
ptr = (int*) malloc(100 * sizeof(int));
```

This statement will allocate either 200 or 400 according to size of `int` 2 or 4 bytes respectively and the pointer points to the address of first byte of memory.

## C calloc()

The name calloc stands for "contiguous allocation".

The only difference between malloc() and calloc() is that, malloc() allocates single block of memory whereas calloc() allocates multiple blocks of memory each of same size and sets all bytes to zero.

### Syntax of calloc()

```c
ptr = (cast-type*)calloc(n, element-size);
```

This statement will allocate contiguous space in memory for an array of n elements. For example:

```c
ptr = (float*) calloc(25, sizeof(float));
```

This statement allocates contiguous space in memory for an array of 25 elements each of size of float, i.e, 4 bytes.

### Difference between `malloc()` and `calloc()`

| calloc()                                                     | malloc()                                                     |
| :----------------------------------------------------------- | ------------------------------------------------------------ |
| calloc() initializes the allocated memory with 0 value.      | malloc() initializes the allocated memory with garbage values. |
| Number of arguments is 2                                     | Number of argument is 1                                      |
| **Syntax :**<br />(cast_type *)calloc(blocks , size_of_block); | **Syntax :**<br />(cast_type *)malloc(Size_in_bytes);        |

## C free()

Dynamically allocated memory created with either calloc() or malloc() doesn't get freed on its own. You must explicitly use free() to release the space.

### syntax of free()

```c
free(ptr);
```

This statement frees the space allocated in the memory pointed by `ptr`.

## Example #1: Using C malloc() and free()

**Write a C program to find sum of n elements entered by user. To perform this program, allocate memory dynamically using malloc() function.**

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &num);

    ptr = (int*) malloc(num * sizeof(int));  //memory allocated using malloc
    if(ptr == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    printf("Enter elements of array: ");
    for(i = 0; i < num; ++i)
    {
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);
    free(ptr);
    return 0;
}
```

## Example #2: Using C calloc() and free()

**Write a C program to find sum of n elements entered by user. To perform this program, allocate memory dynamically using calloc() function.**

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, i, *ptr, sum = 0;
    printf("Enter number of elements: ");
    scanf("%d", &num);

    ptr = (int*) calloc(num, sizeof(int));
    if(ptr == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    printf("Enter elements of array: ");
    for(i = 0; i < num; ++i)
    {
        scanf("%d", ptr + i);
        sum += *(ptr + i);
    }

    printf("Sum = %d", sum);
    free(ptr);
    return 0;
}
```

## C realloc()

If the previously allocated memory is insufficient or more than required, you can change the previously allocated memory size using realloc().

### Syntax of realloc()

```c
ptr = realloc(ptr, newsize);
```

Here, ptr is reallocated with size of newsize.

## Example #3: Using realloc()

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr, i , n1, n2;
    printf("Enter size of array: ");
    scanf("%d", &n1);

    ptr = (int*) malloc(n1 * sizeof(int));

    printf("Address of previously allocated memory: ");
    for(i = 0; i < n1; ++i)
         printf("%u\t",ptr + i);

    printf("\nEnter new size of array: ");
    scanf("%d", &n2);
    ptr = realloc(ptr, n2);
    for(i = 0; i < n2; ++i)
         printf("%u\t", ptr + i);
    return 0;
}
```

