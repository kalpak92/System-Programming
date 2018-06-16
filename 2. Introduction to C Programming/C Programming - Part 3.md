# Pointers and Memory Address

[TOC]

## Physical and virtual memory

- Physical memory: physical resources where data can be stored and accessed by your computer
  - cache
  - RAM
  - hard disk
  - removable storage
- Virtual memory: abstraction by OS, addressable space accessible by your code

### Physical memory considerations

- Different sizes and access speeds
- Memory management – major function of OS
- Optimization – to ensure your code makes the best use of physical memory available
- OS moves around data in physical memory during execution
- Embedded processors – may be very limited

### Virtual memory

- How much physical memory do I have?

  Answer: 2 MB (cache) + 2 GB (RAM) + 100 GB (hard drive) + ...

- How much virtual memory do I have?

  Answer: <4 GB (32-bit OS), typically 2 GB for Windows, 3-4 GB for linux

- Virtual memory maps to different parts of physical memory

- Usable parts of virtual memory: stack and heap

  - stack: where declared variables go
  - heap: where dynamic memory goes

## Pointers and addresses

- Pointer: memory address of a variable
- Address can be used to access/modify a variable from anywhere
- Extremely useful, especially for data structures
- Well known for obfuscating code

### Addressing variables

- Every variable residing in memory has an address!

- What doesn’t have an address?

  - register variables
  - constants/literals/preprocessor defines
  - expressions (unless result is a variable)

- How to find an address of a variable? 

  The & operator

  ```c
  int n = 4;
  double pi = 3.14159;
  int ∗pn = &n; / ∗ address of integer n ∗ /
  double ∗ ppi = &pi ; / ∗ address of double pi ∗ /
  ```

- Address of a variable of type t has type t *

### Dereferencing pointers

- Accessing/modifying addressed variable: dereferencing/indirection operator *****

```c
/ ∗ prints " pi = 3.14159\n " ∗ /
printf ( "pi = %g\n" ,∗ ppi );
/ ∗ pi now equals 7.14159 ∗ /
∗ ppi = ∗ ppi + ∗pn ;
```

- Dereferenced pointer like any other variable
- null pointer, i.e. 0 (NULL): pointer that does not reference anything

### Casting pointers

- Can explicitly cast any pointer type to any other pointer type

```c
ppi = (double ∗)pn; /∗ pn originally of type ( int ∗) ∗/
```

- Implicit cast to/from void * also possible
- Dereferenced pointer has new type, regardless of real type of data

## Arrays and pointers

- Primitive arrays implemented in C using pointer to block of contiguous memory

- Consider array of 8 ints:

  ​	int arr [8];

- Accessing arr using array entry operator:

  ​	int a = arr [0];

- arr is like a pointer to element 0 of the array:

  ​	int ∗pa = arr;  ⇔ int ∗pa = &arr[0];

- Not modifiable/reassignable like a pointer

### The sizeof() operator

- For primitive types/variables, size of type in bytes:

```c
int s = sizeof(char); /∗ == 1 ∗/
double f; /∗ sizeof(f) == 8 ∗/ (64-bit OS)
```

- For primitive arrays, size of array in bytes:

```c
int arr [8]; /∗ sizeof(arr) == 32 ∗/ (64-bit OS)
long arr [5]; /∗ sizeof(arr) == 40 ∗/ (64-bit OS)
```

- Array length

```c
/ ∗ needs to be on one line when implemented ∗ /
#define array _length ( arr ) ( sizeof ( arr ) == 0 ? 0 : sizeof ( arr )/ sizeof (( arr ) [ 0 ] ) )
```

## Pointer vs Array  

Most of the time, pointer and array accesses can be treated as acting the same, the major exceptions being:

- the **sizeof operator**
  - **sizeof(array)** returns the amount of memory used by all elements in array
  - **sizeof(pointer)** only returns the amount of memory used by the pointer variable itself

- the & operator
  - &array is an alias for &array[0] and returns the *address of the first element in array*
  - &pointer returns *the address of pointer*.

- a string literal initialization of a character array
  - char array[] = “abc” sets the ***first four elements in array to ‘a’, ‘b’, ‘c’, and ‘\0’***
  - char *pointer = “abc” sets ***pointer to the address of the “abc”*** string (which may be stored in read-only memory and thus unchangeable)

- Pointer variable can be assigned a value whereas array variable cannot be.

  ​	int a[10];

  ​	int *p; 

  ​	p=a; /*legal*/

  ​	a=p; /*illegal*/ 

- Arithmetic on pointer variable is allowed.

  ​	p++; /*Legal*/

  ​	a++; /*illegal*/ 

- Behavior of sizeof operator

  ```c
  // 1st program to show that array and pointers are different
  #include <stdio.h>
  int main()
  {
     int arr[] = {10, 20, 30, 40, 50, 60};
     int *ptr = arr;
      
     // sizof(int) * (number of element in arr[]) is printed
     printf("Size of arr[] %d\n", sizeof(arr));
   
     // sizeof a pointer is printed which is same for all type 
     // of pointers (char *, void *, etc)
     printf("Size of ptr %d", sizeof(ptr));
     return 0;
  }
  ```

  Output

  ```shell
  Size of arr[] 24
  Size of ptr 4
  ```

- Assigning any address to an array variable is not allowed.

  ```c
  #include <stdio.h>
  int main()
  {
     int arr[] = {10, 20}, x = 10;
     int *ptr = &x; // This is fine
     arr = &x;  // Compiler Error
     return 0;
  }
  ```

  Output:

  ```shell
   Compiler Error: incompatible types when assigning to 
   	type 'int[2]' from type 'int *'   
  ```

### Similarities

- Array name gives address of first element of array.  

  Consider the following program for example. 

  ```c
  #include <stdio.h>
  int main()
  {
     int arr[] = {10, 20, 30, 40, 50, 60};
     int *ptr = arr;  // Assigns address of array to ptr
     printf("Value of first element is %d", *ptr);
     return 0;
  }
  ```

  Output

  ```shell
  Value of first element is 10
  ```

- Array members are accessed using pointer arithmetic.  

  Compiler uses pointer arithmetic to access array element. For example, an expression like “arr[i]” is treated as *(arr + i) by the compiler. That is why the expressions like *(arr + i) work for array arr, and expressions like ptr[i] also work for pointer ptr.

  ```c
  #include <stdio.h>
  int main()
  {
     int arr[] = {10, 20, 30, 40, 50, 60};
     int *ptr = arr;
     printf("arr[2] = %d\n", arr[2]);
     printf("*(arr + 2) = %d\n", *(arr + 2));
     printf("ptr[2] = %d\n", ptr[2]);
     printf("*(ptr + 2) = %d\n", *(ptr + 2));
     return 0;
  }
  ```

  Output

  ```shell
  arr[2] = 30
  *(arr + 2) = 30
  ptr[2] = 30
  *(ptr + 2) = 30
  ```

- Array parameters are always passed as pointers, even when we use square brackets. 

  ```c
  #include <stdio.h>
   
  int fun(int ptr[])
  {
     int x = 10;
   
     // size of a pointer is printed
     printf("sizeof(ptr) = %d\n", sizeof(ptr));
   
     // This allowed because ptr is a pointer, not array
     ptr = &x;
   
     printf("*ptr = %d ", *ptr);
   
     return 0;
  }
  int main()
  {
     int arr[] = {10, 20, 30, 40, 50, 60};
     fun(arr);
     return 0;
  }
  ```

  Output

  ```shell
  sizeof(ptr) = 4
  *ptr = 10
  ```

### Difference between single quoted and double quoted declaration of char array?

In C/C++, when a character array is initialized with a double quoted string and array size is not specified, compiler automatically allocates one extra space for string terminator ‘\0’. For example, following program prints 6 as output.

```c
#include<stdio.h>
int main()
{
  char arr[] = "geeks"; // size of arr[] is 6 as it is '\0' terminated
  printf("%d", sizeof(arr));
  getchar();
  return 0;
}
```

If array size is specified as 5 in the above program then the program works without any warning/error and prints 5 in C, but causes compilation error in C++.

```c
#include<stdio.h>
int main()
{
  char arr[5] = "geeks";  // arr[] is not terminated with '\0'
                          // and its size is 5
  printf("%d", sizeof(arr));
  getchar();
  return 0;
}
```

When character array is initialized with comma separated list of characters and array size is not specified, compiler doesn’t create extra space for string terminator ‘\0’. For example, following program prints 5.

```c
#include<stdio.h>
int main()
{
  char arr[]= {'g', 'e', 'e', 'k', 's'}; // arr[] is not terminated with '\0' and its size is 5
  printf("%d", sizeof(arr));
  getchar();
  return 0;
}
```

## Are array members deeply copied?

In C/C++, we can assign a struct (or class in C++ only) variable to another variable of same type. When we assign a struct variable to another, all members of the variable are copied to the other struct variable. But what happens when the structure contains pointer to dynamically allocated memory and what if it contains an array?

In the following C++ program, struct variable st1 contains ***pointer to dynamically allocated memory***. When we assign st1 to st2, str pointer of st2 also start pointing to same memory location. This kind of copying is called **Shallow Copy**.

```c++
# include <iostream>
# include <string.h>
using namespace std;
struct test
{
  char *str;
};
 
int main()
{
  struct test st1, st2;
 
  st1.str = new char[20];
  strcpy(st1.str, "GeeksforGeeks");
 
  st2 = st1;
 
  st1.str[0] = 'X';
  st1.str[1] = 'Y';
 
  /* Since copy was shallow, both strings are same */
  cout << "st1's str = " << st1.str << endl;
  cout << "st2's str = " << st2.str << endl;
 
  return 0;
}
```

Output

```shell
Output:
st1’s str = XYeksforGeeks
st2’s str = XYeksforGeeks
```

Now, what about arrays? **The point to note is that the array members are not shallow copied, compiler automatically performs Deep Copy *for array members***. 

In the following program, struct test contains array member str[]. When we assign st1 to st2, st2 has a new copy of the array. So st2 is not changed when we change str[] of st1. 

```c++
# include <iostream>
# include <string.h>
 
using namespace std;
 
struct test
{
  char str[20];
};
 
int main()
{
  struct test st1, st2;
 
  strcpy(st1.str, "GeeksforGeeks");
 
  st2 = st1;
 
  st1.str[0] = 'X';
  st1.str[1] = 'Y';
 
  /* Since copy was Deep, both arrays are different */
  cout << "st1's str = " << st1.str << endl;
  cout << "st2's str = " << st2.str << endl;
 
  return 0;
}
```

Output

```shell
st1’s str = XYeksforGeeks
st2’s str = GeeksforGeeks
```

## What’s difference between char s[] and char *s in C?

Consider below two statements in C. What is difference between two?

```c
char s[] = "geeksquiz";
char *s  = "geeksquiz";
```

The statements ‘**char s[] = “geeksquiz”**‘ creates a character array which is like any other array and we can do all array operations. The only special thing about this array is, although we have initialized it with 9 elements, its size is 10 (Compiler automatically adds ‘\0').

```c
#include <stdio.h>
int main()
{
    char s[] = "geeksquiz";
    printf("%lu", sizeof(s));
    s[0] = 'j';
    printf("\n%s", s);
    return 0;
}
```

Output:

```shell
10
jeeksquiz
```

The statement ‘**char \*s = “geeksquiz”** creates a string literal. The string literal is stored in read only part of memory by most of the compilers. The C and C++ standards say that string literals have static storage duration, any attempt at modifying them gives undefined behavior.  **s** is just a pointer and like any other pointer stores address of string literal. 

```c
#include <stdio.h>
int main()
{
    char *s = "geeksquiz";
    printf("%lu", sizeof(s));
 
    // Uncommenting below line would cause undefined behaviour
    // (Caused segmentation fault on gcc)
    //  s[0] = 'j';  
    return 0;
}
```

Output

```shell
8
```

Running above program may generates a warning also “warning: deprecated conversion from string constant to ‘char*’”. This warning occurs because s is not a const pointer, but stores address of read only location. The warning can be avoided by pointer to const.

```c
#include <stdio.h>
int main()
{
    const char *s = "geeksquiz";
    printf("%lu", sizeof(s));
    return 0;
}
```

## Dangling, Void, Null and Wild Pointers

### Dangling pointer

A pointer pointing to a memory location that has been deleted (or freed) is called dangling pointer. There are **three** different ways where Pointer acts as dangling pointer.

- **De-allocation of memory**

  ```c
  // Deallocating a memory pointed by ptr causes
  // dangling pointer
  #include <stdlib.h>
  #include <stdio.h>
  int main()
  {
      int *ptr = (int *)malloc(sizeof(int));
   
      // After below free call, ptr becomes a 
      // dangling pointer
      free(ptr); 
       
      // No more a dangling pointer
      ptr = NULL;
  }
  ```

- **Function Call**

  ```c
  // The pointer pointing to local variable becomes
  // dangling when local variable is static.
  #include<stdio.h>
   
  int *fun()
  {
      // x is local variable and goes out of
      // scope after an execution of fun() is
      // over.
      int x = 5;
   
      return &x;
  }
   
  // Driver Code
  int main()
  {
      int *p = fun();
      fflush(stdin);
   
      // p points to something which is not
      // valid anymore
      printf("%d", *p);
      return 0;
  }
  ```

  Output

  ```shell
  A garbage Address 
  ```

  The above problem doesn’t appear (or p doesn’t become dangling) if x is a static variable. 

  ```c
  // The pointer pointing to local variable doesn't
  // become dangling when local variable is static.
  #include<stdio.h>
   
  int *fun()
  {
      // x now has scope throughout the program
      static int x = 5;
   
      return &x;
  }
   
  int main()
  {
      int *p = fun();
      fflush(stdin);
       
      // Not a dangling pointer as it points
      // to static variable.
      printf("%d",*p);
  }
  ```

  Output

  ```shell
  5
  ```

- **Variable goes out of scope** 

  ```c
  void main()
  {
     int *ptr;
     .....
     .....
     {
         int ch;
         ptr = &ch;
     } 
     .....   
     // Here ptr is dangling pointer
  }
  ```

### Void pointer

Void pointer is a specific pointer type – void * – a pointer that points to some data location in storage, which doesn’t have any specific type. Void refers to the type. Basically the type of data that it points to is can be any. If we assign address of char data type to void pointer it will become char Pointer, if int data type then int pointer and so on. Any pointer type is convertible to a void pointer hence it can point to any value.
Important Points

- void pointers **cannot be dereferenced**. It can however be done using typecasting the void pointer
- Pointer arithmetic is not possible on pointers of void due to lack of concrete value and thus size.

```c
#include<stdlib.h>
#inlcude <stdio.h>
 
int main()
{
    int x = 4;
    float y = 5.5;
     
    //A void pointer
    void *ptr;
    ptr = &x;
 
    // (int*)ptr - does type casting of void 
    // *((int*)ptr) dereferences the typecasted 
    // void pointer variable.
    printf("Integer variable is = %d", *( (int*) ptr) );
 
    // void pointer is now float
    ptr = &y; 
    printf("\nFloat variable is= %f", *( (float*) ptr) );
 
    return 0;
}

```

### NULL Pointer

NULL Pointer is a pointer which is pointing to nothing. In case, if we don’t have address to be assigned to a pointer, then we can simply use NULL.

```c
#include <stdio.h>
int main()
{
    // Null Pointer
    int *ptr = NULL;
     
    printf("The value of ptr is %u", ptr);
    return 0;
}
```

**Important Points**

- **NULL vs Uninitialized pointer –** An uninitialized pointer stores an undefined value. A null pointer stores a defined value, but one that is defined by the environment to not be a valid address for any member or object.
- **NULL vs Void Pointer** – Null pointer is a value, while void pointer is a type

### Wild pointer

A pointer which has not been initialized to anything (not even NULL) is known as wild pointer. The pointer may be initialized to a non-NULL garbage value that may not be a valid address.

```c
int main()
{
    int *p;  /* wild pointer */
 
    int x = 10;
 
    // p is not a wild pointer now
    p = &x;
 
    return 0;
}
```

## Strings as arrays

- Strings stored as null-terminated character arrays (last character == ’\0’)

- Suppose 

  ​	char str [] = "This is a string."; and
  	char ∗ pc = str ;

- Manipulate string as you would an array

  ​	∗(pc+10) = ’S’;

  ​	puts(str ); /∗ prints "This is a String ." ∗/

### String utility functions

- String functions in standard header string.h
- Copy functions: strcpy(), strncpy()
  - **char ∗ strcpy(strto ,strfrom);** – copy strfrom to strto
  - **char ∗ strncpy(strto ,strfrom,n);** – copy n chars from strfrom to strto
- Comparison functions: strcmp(), strncmp()
  - **int strcmp(str1,str2 );** – compare str1, str2; return 0 if equal, positive if str1>str2, negative if str1<str2
  - **int strncmp(str1,str2,n);** – compare first n chars of str1 and str2
- String length: strlen()
  - **int strlen ( str );** – get length of str

- Concatenation functions: strcat(), strncat()
  - **char ∗ strcat(strto ,strfrom);** – add strfrom to end of strto
  - **char ∗ strncat(strto ,strfrom,n);** – add n chars from strfrom to end of strto
- Search functions: strchr(), strrchr()
  - **char ∗ strchr(str ,c);** – find char c in str, return pointer to first occurrence, or NULL if not found
  - **char ∗ strrchr (str ,c);** – find char c in str, return pointer to last occurrence, or NULL if not found

## Difference between sizeof and strlen

- strlen() is used to get the length of an array of chars / string.
- sizeof() is used to get the actual size of any type of data in bytes.

Besides, ***sizeof() is a compile-time expression giving you the size of a type or a variable's type***. It doesn't care about the value of the variable.

***strlen() is a function that takes a pointer to a character, and walks the memory from this character on, looking for a NULL character***. It counts the number of characters before it finds the NULL character. In other words, it gives you the length of a C-style NULL-terminated string.

The two are almost different. In C++, you do not need either very much, strlen() is for C-style strings, which should be replaced by C++-style std::strings, whereas the primary application for sizeof() in C is as an argument to functions like malloc(), memcpy() or memset(), all of which you shouldn't use in C++ (use new, std::copy(), and std::fill() or constructors). 

```c
char *str1 = "Sanjeev";
char str2[] = "Sanjeev";

printf("%d %d\n",strlen(str1),sizeof(str1));    
printf("%d %d\n",strlen(str2),sizeof(str2));
```

Output:

```
7 4
7 8
```

Because sizeof gives you the size in bytes of the data type. ***The data type of str1 is char* which 4 bytes***. In contrast, [strlen](http://www.kernel.org/doc/man-pages/online/pages/man3/strlen.3.html) gives you the length of the string in chars not including the null terminator, thus 7. ***The sizeof str2 is char array of 8 bytes***, which is the number of chars including the null terminator.

str1 is a pointer to char and size of a pointer variable on your system is 4.
 str2 is a array of char on stack, which stores 8 characters, "s","a","n","j","e","e","v","\0" so its size is 8

***Important to note that size of pointer to various data type will be same, because they are pointing to different data types but they occupy only size of pointer on that system.***

### Question

Why does n not equal to 8 in the following function?

```c
void foo(char cvalue[8])
{
	int n = sizeof (cvalue);
}
```

But n *does* equal to 8 in this version of the function:

```c
void bar()
{
	char cvalue[8];
	int n = sizeof (cvalue);
}
```

Answer:

Because you can't pass entire arrays as function parameters in C. **You're actually passing a pointer to it; the brackets are syntactic sugar.** There are no guarantees the array you're pointing to has size 8, since you could pass this function any character pointer you want.

// These all do the same thing

`void foo(char cvalue[8])`

`void foo(char cvalue[])`

`void foo(char *cvalue)`

# User defined datatype

## Structure

Definition: A structure is a collection of related variables (of possibly different types) grouped together under a single name.
This is a an example of composition–building complex structures out of simple ones.

```c
struct point
{
    int x;
    int y;
};

struct employee
{
    char name[100];
    char lname[100];
    int age;
};
```

- struct defines a new datatype.

- The name of the structure is optional.

  **struct {...} x,y,z;**

- The variables declared within a structure are called its  members.

- Variables can be declared like any other built in data-type.

  **struct point ptA;**

- Initialization is done by specifying values of every member.

  **struct point ptA={10,20};**

- Assignment operator copies every member of the structure (be careful with pointers).

```c
/* Members can be structures */
struct triangle
{
    struct point ptA;
    struct point ptB;
    struct point ptC;
};

/* Members can be self referential */
struct chain_element
{
    int data;
    struct chain_element  *next;
};
```

- Individual members can be accessed using **’.’** operator.

  ***struct point pt={10,20}; ***

  ***int x=pt.x; int y=pt.y;***

- **If structure is nested, multiple ’.’ are required**

```c
struct rectangle
{
	struct point t l ; / ∗ top l e f t ∗ /
	struct point br ; / ∗ bot right ∗ /
};
struct rectangle rect ;
int tlx = rect.tl.x ; / ∗ nested ∗ /
int tly = rect.tl.y ;
```

### Structure pointers

- Structures are copied element wise.

- For large structures it is more efficient to pass pointers.

  ***void foo(struct point ∗ pp);*** 

  ***struct point pt;*** 

  ***foo(&pt)***

- Members can be accesses from structure pointers using ’->’ operator.

```c
struct point p={10 ,20};
struct point ∗ pp=&p ;
pp−>x = 10; / ∗ changes p . x ∗ /
int y= pp−>y ; / ∗ same as y=p. y ∗ /
```

- Other ways to access structure members?

```c
struct point p={10 ,20};
struct point ∗ pp=&p ;
(∗ pp ). x = 10; / ∗ changes p . x ∗ /
int y= (∗ pp ). y ; / ∗ same as y=p. y ∗ /
```

### Arrays of structures

- Declaring arrays of int: int x[10];
- Declaring arrays of structure: struct point p[10];
- Initializing arrays of int: int x [4]={0,20,10,2};
- Initializing arrays of structure:

		***struct point p[3] = {{0,1}, {10,20}, {30,12}};**

### Size of structures

- The size of a structure is greater than or equal to the sum of the sizes of its members.
- Alignment

```c
struct {
char c ;
/ ∗ padding ∗ /
int i ;
```

- Why is this an important issue? libraries, precompiled files, SIMD instructions.

- Members can be explicitly aligned using compiler extensions.

  \__attribute__((aligned(x))) 	/∗gcc∗/
  __declspec((aligned(x))) 	/∗MSVC∗/

### Struct Hack

What will be the size of following structure?

```c
struct employee
{
    int     emp_id;
    int     name_len;
    char    name[0];
};
```

4 + 4 + 0 = 8 bytes.

And what about size of “name[0]”. In gcc, when we create an array of zero length, it is considered as array of incomplete type that’s why gcc reports its size as “0” bytes. This technique is known as “Stuct Hack”. 

***When we create array of zero length inside structure, it must be (and only) last member of structure.*** 

“Struct Hack” technique is used to create ***variable length member in a structure***. In the above structure, string length of “name” is not fixed, so we can use “name” as variable length array. 

Let us see below memory allocation. 

`struct employee *e = malloc(sizeof(*e) + sizeof(char) * 128);`

is equivalent to

```c
struct employee
{
    int     emp_id;
    int     name_len;
    char    name[128]; /* character array of size 128 */
};
```

Another example: 

`struct employee *e = malloc(sizeof(*e) + sizeof(char) * 1024);`

is equivalent to

```c
struct employee
{
    int     emp_id;
    int     name_len;
    char    name[1024]; /* character array of size 1024 */
};
```

Now we can use “name” same as pointer. e.g.

```c
e->emp_id          = 100;
e->name_len        = strlen("Geeks For Geeks");
strncpy(e->name, "Geeks For Geeks", e->name_len);
```

When we allocate memory as given above, compiler will allocate memory to store “emp_id” and “name_len” plus contiguous memory to store “name”. When we use this technique, gcc guaranties that, “name” will get contiguous memory.

### Structure Padding

In order to align the data in memory, one or more empty bytes (addresses) are inserted (or left empty) between memory addresses which are allocated for other structure members while memory allocation. This concept is called structure padding.

Architecture of a computer processor is such a way that it can read 1 word (4 byte in 32 bit processor) from memory at a time.

To make use of this advantage of processor, data are always aligned as 4 bytes package which leads to insert empty addresses between other member’s address.

Because of this structure padding concept in C, size of the structure is always not same as what we think.

For example, please consider below structure that has 5 members.

```c
struct student
{
       int id1;
       int id2;
       char a;
       char b;
       float percentage;
};
```

As per C concepts, int and float data types occupy 4 bytes each and char data type occupies 1 byte for 32 bit processor. So, only 14 bytes (4+4+1+1+4) should be allocated for above structure.

But, this is wrong.  Do you know why?

Architecture of a computer processor is such a way that it can read 1 word from memory at a time.

1 word is equal to 4 bytes for 32 bit processor and 8 bytes for 64 bit processor. So, 32 bit processor always reads 4 bytes at a time and 64 bit processor always reads 8 bytes at a time.

This concept is very useful to increase the processor speed.

To make use of this advantage, **memory is arranged as a group of 4 bytes in 32 bit processor and 8 bytes in 64 bit processor.**

Below C program is compiled and executed in 32 bit compiler. Please check memory allocated for structure1 and structure2 in below program.

```c
#include <stdio.h>
#include <string.h>
/*  Below structure1 and structure2 are same. 
    They differ only in member's alignment */
struct structure1 
{
       int id1;
       int id2;
       char name;
       char c;
       float percentage;
};
 
struct structure2 
{
       int id1;
       char name;
       int id2;
       char c;
       float percentage;                      
};
 
int main() 
{
    struct structure1 a;
    struct structure2 b;
 
    printf("size of structure1 in bytes : %d\n", 
            sizeof(a));
    printf ( "\n   Address of id1        = %u", &a.id1 );
    printf ( "\n   Address of id2        = %u", &a.id2 );
    printf ( "\n   Address of name       = %u", &a.name );
    printf ( "\n   Address of c          = %u", &a.c );
    printf ( "\n   Address of percentage = %u",
                   &a.percentage );
 
    printf("   \n\nsize of structure2 in bytes : %d\n",
                   sizeof(b));
    printf ( "\n   Address of id1        = %u", &b.id1 );
    printf ( "\n   Address of name       = %u", &b.name );
    printf ( "\n   Address of id2        = %u", &b.id2 );
    printf ( "\n   Address of c          = %u", &b.c );
    printf ( "\n   Address of percentage = %u",
                   &b.percentage );
    getchar();
    return 0;
}

```

**OUTPUT** :

```shell
size of structure1 in bytes : 16
Address of id1 = 1297339856
Address of id2 = 1297339860
Address of name = 1297339864
Address of c = 1297339865
Address of percentage = 1297339868

size of structure2 in bytes : 20
Address of id1 = 1297339824
Address of name = 1297339828
Address of id2 = 1297339832
Address of c = 1297339836
Address of percentage = 1297339840
```

#### How to avoid structure padding in C?

- \#pragma      pack ( 1 ) directive can be used for arranging memory for structure      members very next to the end of other structure members.
- VC++      supports this feature. But, some compilers such as Turbo C/C++ does not      support this feature.
- Please      check the below program where there will be no addresses (bytes) left      empty because of structure padding.

```c
#include <stdio.h>
#include <string.h>
 
/*  Below structure1 and structure2 are same. 
    They differ only in member's allignment */
 
#pragma pack(1)
struct structure1 
{
       int id1;
       int id2;
       char name;
       char c;
       float percentage;
};
 
struct structure2 
{
       int id1;
       char name;
       int id2;
       char c;
       float percentage;                      
};
 
int main() 
{
    struct structure1 a;
    struct structure2 b;
 
    printf("size of structure1 in bytes : %d\n",
                   sizeof(a));
    printf ( "\n   Address of id1        = %u", &a.id1 );
    printf ( "\n   Address of id2        = %u", &a.id2 );
    printf ( "\n   Address of name       = %u", &a.name );
    printf ( "\n   Address of c          = %u", &a.c );
    printf ( "\n   Address of percentage = %u", 
                   &a.percentage );
 
    printf("   \n\nsize of structure2 in bytes : %d\n", 
                   sizeof(b));
    printf ( "\n   Address of id1        = %u", &b.id1 );
    printf ( "\n   Address of name       = %u", &b.name );
    printf ( "\n   Address of id2        = %u", &b.id2 );
    printf ( "\n   Address of c          = %u", &b.c );
    printf ( "\n   Address of percentage = %u", 
                   &b.percentage );
    getchar();
    return 0;
}

```

Output:

```shell
size of structure1 in bytes : 14
Address of id1 = 3438103088
Address of id2 = 3438103092
Address of name = 3438103096
Address of c = 3438103097
Address of percentage = 3438103098

size of structure2 in bytes : 14
Address of id1 = 3438103072
Address of name = 3438103076
Address of id2 = 3438103077
Address of c = 3438103081
Address of percentage = 3438103082
```

## Union

A union is a variable that may hold objects of different types/sizes in the same memory location. 

Example:

```c
union data
{
	int idata ;
	float fdata ;
	char∗ sdata ;
} d1 ,d2 ,d3;

d1. idata =10;
d1. fdata =3.14F;
d1. sdata="hello world" ;
```

- The size of the union variable is equal to the size of its largest element.

- Important: The compiler does not test if the data is being read in the correct format.

  union data d; 

  d.idata=10; float f=d.fdata; /∗ will give junk

- A common solution is to maintain a separate variable.

```c
enum dtype {INT ,FLOAT,CHAR};
struct variant
{
	union data d;
	enum dtype t ;
};
```

We can access only one member of union at a time. We can’t access all member values at the same time in union. But, structure can access all member values at the same time. This is because, Union allocates one common storage space for all its members. Where as Structure allocates storage space for all its members separately.

Many union variables can be created in a program and memory will be allocated for each union variable separately.

Below table will help you how to form a C union, declare a union, initializing and accessing the members of the union.

| **Using normal variable**                                    | **Using pointer variable**                                   |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Syntax:**    union tag_name    {    data type var_name1;    data type var_name2;    data type var_name3;    }; | **Syntax:**    union tag_name    {    data type var_name1;    data type var_name2;    data type var_name3;    }; |
| **Example:**    union student    {    int  mark;    char name[10];    float average;    }; | **Example:**    union student    {    int  mark;    char name[10];    float average;    }; |
| **Declaring union using normal variable:**    union student report; | **Declaring union using pointer variable:**    union student *report, rep; |
| **Initializing union using normal variable:**    union student report = {100, “Mani”, 99.5}; | **Initializing union using pointer variable:**    union student rep = {100, “Mani”, 99.5};    report = &rep; |
| **Accessing union members using normal variable:**    report.mark;    report.name;    report.average; | **Accessing union members using pointer variable:**    report  -> mark;    report -> name;    report -> average; |

```c
#include <stdio.h>
#include <string.h>
 
union student 
{
            char name[20];
            char subject[20];
            float percentage;
};
 
int main() 
{
    union student record1;
    union student record2;
 
    // assigning values to record1 union variable
       strcpy(record1.name, "Raju");
       strcpy(record1.subject, "Maths");
       record1.percentage = 86.50;
 
       printf("Union record1 values example\n");
       printf(" Name       : %s \n", record1.name);
       printf(" Subject    : %s \n", record1.subject);
       printf(" Percentage : %f \n\n", record1.percentage);
 
    // assigning values to record2 union variable
       printf("Union record2 values example\n");
       strcpy(record2.name, "Mani");
       printf(" Name       : %s \n", record2.name);
 
       strcpy(record2.subject, "Physics");
       printf(" Subject    : %s \n", record2.subject);
 
       record2.percentage = 99.50;
       printf(" Percentage : %f \n", record2.percentage);
       return 0;
}

```

**OUTPUT**:

```shell
Union record1 values example
Name :
Subject :
Percentage : 86.500000;
Union record2 values example
Name : Mani
Subject : Physics
Percentage : 99.500000

```

**DIFFERENCE BETWEEN STRUCTURE AND UNION IN C:**

| **C Structure**                                              | **C Union**                                                  |
| :----------------------------------------------------------- | ------------------------------------------------------------ |
| Structure   allocates storage space for all its members separately. | Union allocates one common storage space for all its members.    Union finds that which of its member needs high storage space   over other members and allocates that much space |
| Structure occupies higher memory space.                      | Union occupies lower memory space over structure.            |
| We can access all members of structure at a time.            | We can access only one member of union at a time.            |
| Structure example:    <br />struct student    {    <br />int mark;    char name[6];    double average;    }; | Union example:    <br />union student    {   <br /> int mark;    char name[6];    double average;    }; |
| For above structure, memory allocation will be like below.    int mark – 2B    char name[6] – 6B    double average – 8B     Total memory allocation = 2+6+8 = 16 Bytes | For above union, only 8 bytes of memory will be allocated since   double data type will occupy maximum space of memory over other data   types.     Total memory allocation = 8 Bytes |

## Bit fields

Definition: A bit-field is a set of adjacent bits within a single ’word’. 

Example:

```
struct flag {
unsigned i n t is _color :1;
unsigned i n t has_sound : 1 ;
unsigned i n t is _ntsc :1;
};
```

- the number after the colons specifies the width in bits.
- each variables should be declared as **unsigned int**

# Pointers to pointers

- Address stored by pointer also data in memory

- Can address location of address in memory – pointer to that pointer

  ```c
  int n = 3;
  int ∗pn = &n; / ∗ pointer to n ∗ /
  int ∗∗ppn = &pn; / ∗ pointer to address of n ∗ /
  ```

- Many uses in C: pointer arrays, string arrays.

### Swapping pointers

 The first thing you need to understand is that when you pass something to a function, that something is copied to the function's arguments.

Suppose you have the following:

```c
void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    assert(a == 17);
    assert(b == 42);
    // they're swapped!
}

int x = 42;
int y = 17;
swap1(x, y);
assert(x == 42);
assert(y == 17);
// no, they're not swapped!
```

The original variables will not be swapped, because their values are copied into the function's arguments. The function then proceeds to swap the values of those arguments, and then returns. The original values are not changed, because the function only swaps its own private copies.

Now how do we work around this? The function needs a way to refer to the original variables, not copies of their values. How can we refer to other variables in C? Using pointers.

If we pass pointers to our variables into the function, the function can swap the values in *our* variables, instead of its own argument copies.

```c
void swap2(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    assert(*a == 17);
    assert(*b == 42);
    // they're swapped!
}

int x = 42;
int y = 17;
swap2(&x, &y); // give the function pointers to our variables
assert(x == 17);
assert(y == 42);
// yes, they're swapped!
```

Notice how inside the function we're not assigning to the pointers, but assigning to what they point to. And the pointers point to our variables `x` and `y`. The function is changing directly the values stored in *our* variables through the pointers we give it. And that's exactly what we needed.

Now what happens if we have two pointer variables and want to swap the *pointers* themselves (as opposed to the values they point to)?

***If we pass pointers, the pointers will simply be copied (not the values they point to) to the arguments.***

```c
void swap3(int* a, int* b) {
    int* temp = a;
    a = b;
    b = temp;
    assert(*a == 17);
    assert(*b == 42);
    // they're swapped!
}
void swap4(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    assert(*a == 17);
    assert(*b == 42);
    // they're swapped!
}

int x = 42;
int y = 17;
int* xp = &x;
int* yp = &y;

swap3(xp, yp);
assert(xp == &x);
assert(yp == &y);
assert(x == 42);
assert(y == 17);
// Didn't swap anything!

swap4(xp, yp);
assert(xp == &x);
assert(yp == &y);
assert(x == 17);
assert(y == 42);
// Swapped the stored values instead!
```

The function `swap3` only ***swaps its own private copies of our pointers that it gets in its arguments***. It's the same issue we had with `swap1`. And `swap4` is changing the values our variables point to, not the pointers! 

We're giving the function a means to refer to the variables `x` and `y` but we want them to refer to `xp` and `yp`.

How do we do that? We pass it their addresses!

```c
void swap5(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
    assert(**a == 17);
    assert(**b == 42);
    // they're swapped!
}


int x = 42;
int y = 17;
int* xp = &x;
int* yp = &y;
swap5(&xp, &yp);
assert(xp == &y);
assert(yp == &x);
assert(x == 42);
assert(y == 17);
// swapped only the pointers variables
```

This way it swaps our pointer variables (notice how `xp` now points to `y`) but not the values they point to. We gave it a way to refer to our pointer variables, so it can change them!

By now it should be easy to understand how to swap two strings in the form of `char*` variables. The swap function needs to receive pointers to `char*`.

```c
void swapStrings(char** a, char** b){
    char *temp = *a;
    *a = *b;
    *b = temp;
    assert(strcmp(*a, "world") == 0);
    assert(strcmp(*b, "Hello") == 0);
}

char* x = "Hello";
char* y = "world";
swapStrings(&x, &y);
assert(strcmp(x, "world") == 0);
assert(strcmp(y, "Hello") == 0);
```

## Pointer arrays

- Pointer array – array of pointers
  - int ∗arr [20]; – an array of pointers to int’s
  - char ∗arr[10]; – an array of pointers to char’s
- Pointers in array can point to arrays themselves
  - char ∗strs [10]; – an array of char arrays (or strings)

Example:

- Have an array int arr [100]; that contains some numbers
- Want to have a sorted version of the array, but not modify arr
- Can declare a pointer array int ∗ sorted_array[100]; containing pointers to elements of arr and sort the pointers instead of the numbers themselves
- Good approach for sorting arrays whose elements are very large (like strings)

### String arrays

- An array of strings, each stored as a pointer to an array of chars

- Each string may be of different length

  ```c
  char str1 [ ] = "hello" ; / ∗ length = 6 ∗ /
  char str2 [ ] = "goodbye" ; / ∗ length = 8 ∗ /
  char str3 [ ] = "ciao" ; / ∗ length = 5 ∗ /
  char strArray [ ] = { str1 , str2 , str3 };
  ```

  Note that strArray contains only pointers, not the characters themselves!

# Void pointers

- C does not allow us to declare and use void variables.

- void can be used only as return type or parameter of a function.

- C allows void pointers

- Question: What are some scenarios where you want to pass void pointers?

  - void pointers can be used to point to any data type

    ```C
    int x; 
    void∗ p=&x; /∗points to int ∗/
    float f;
    void∗ p=&f; /∗points to float ∗/
    ```

- **void pointers cannot be dereferenced**. The pointers should always be cast before dereferencing.

```c
void∗ p; printf ("%d",∗p); /∗ invalid ∗/
void∗ p; int ∗px=(int∗)p; printf ("%d",∗px); /∗valid ∗/
```

# Function pointers

- In some programming languages, functions are first class variables (can be passed to functions, returned from functions etc.).

- In C, function itself is not a variable. But it is possible to declare pointer to functions.

- Declaration examples:

  ```c
  int (∗fp )( int ) /∗notice the () ∗/
  int (∗fp )(void∗,void∗)
  ```

  Why do we need an extra bracket around function pointers like fun_ptr in above example?  

  If we remove bracket, then the expression “void (*fun_ptr)(int)” becomes “void *fun_ptr(int)” which is declaration of a function that returns void pointer. 

- Function pointers can be assigned, pass to and from functions, placed in arrays etc.

Example

```c
#include <stdio.h>
// A normal function with an int parameter
// and void return type
void fun(int a)
{
    printf("Value of a is %d\n", a);
}
 
int main()
{
    // fun_ptr is a pointer to function fun() 
    void (*fun_ptr)(int) = &fun;
 
    /* The above line is equivalent of following two
       void (*fun_ptr)(int);
       fun_ptr = &fun; 
    */
 
    // Invoking fun() using fun_ptr
    (*fun_ptr)(10);
 
    return 0;
}
```

Output

```shell
Value of a is 10
```

### Some interesting facts about Function Pointers

1. Unlike normal pointers, a function pointer points to code, not data. Typically a function pointer stores the start of executable code.

2. Unlike normal pointers, we do not allocate de-allocate memory using function pointers.

3. A function’s name can also be used to get functions’ address. For example, in the below program, we have removed address operator ‘&’ in assignment. We have also changed function call by removing *, the program still works.

   ```c
   #include <stdio.h>
   // A normal function with an int parameter
   // and void return type
   void fun(int a)
   {
       printf("Value of a is %d\n", a);
   }
    
   int main()
   { 
       void (*fun_ptr)(int) = fun;  // & removed
    
       fun_ptr(10);  // * removed
    
       return 0;
   }
   ```

4. Function pointer can be used in place of switch case. For example, in below program, user is asked for a choice between 0 and 2 to do different tasks.

   ```c
   #include <stdio.h>
   void add(int a, int b)
   {
       printf("Addition is %d\n", a+b);
   }
   void subtract(int a, int b)
   {
       printf("Subtraction is %d\n", a-b);
   }
   void multiply(int a, int b)
   {
       printf("Multiplication is %d\n", a*b);
   }
    
   int main()
   {
       // fun_ptr_arr is an array of function pointers
       void (*fun_ptr_arr[])(int, int) = {add, subtract, multiply};
       unsigned int ch, a = 15, b = 10;
    
       printf("Enter Choice: 0 for add, 1 for subtract and 2 "
               "for multiply\n");
       scanf("%d", &ch);
    
       if (ch > 2) return 0;
    
       (*fun_ptr_arr[ch])(a, b);
    
       return 0;
   }
   ```

5. Like normal data pointers, a function pointer can be passed as an argument and can also be returned from a function.  For example, consider the following C program where wrapper() receives a void fun() as parameter and calls the passed function. 

   ```c
   // A simple C program to show function pointers as parameter
   #include <stdio.h>
    
   // Two simple functions
   void fun1() { printf("Fun1\n"); }
   void fun2() { printf("Fun2\n"); }
    
   // A function that receives a simple function
   // as parameter and calls the function
   void wrapper(void (*fun)())
   {
       fun();
   }
    
   int main()
   {
       wrapper(fun1);
       wrapper(fun2);
       return 0;
   }
   ```

### Callbacks

Callback is a piece of executable code passed to functions. In C, callbacks are implemented by passing function pointers.

You call a function `f()` passing the address of another function `g()`, and `f()` calls `g()` for some specific task. If you pass `f()` the address of `h()`instead, then `f()` will call back `h()` instead. 

Basically, this is a way to **\*parametrize***  a function: Some part of its behavior is not hard-coded into `f()`, but into the callback function. Callers can make `f()` behave differently by passing different callback functions.

### Where Function pointers are stored ?

It depends on where you declare it. It is generally stored on the stack, just like sum or any other local variables, like if you had a char * or int * variable. You could dynamically allocate space for a function pointer, and have it be stored on the heap, or declare it as a global or static local, and have it be stored with the other global and static local variables, but that is less common.    

Remember, a function pointer is just a pointer, so all it contains is the address. It doesn't store the function itself (i.e. no code or variables).

### Array of function pointers

Consider the case where different functions are called based on a value.

```c
enum TYPE{SQUARE,RECT,CIRCILE ,POLYGON};
struct shape {
	float params[MAX] ;
	enum TYPE type ;
};
void draw ( struct shape∗ ps )
{
	switch ( ps−>type )
	{
		case SQUARE:
			draw_square (ps ); break ;
		case RECT:
			draw_rect (ps ); break ;
. . .
	}
}
```

The same can be done using an array of function pointers instead.

```c
void (∗ fp [ 4 ] ) ( struct shape∗ ps)= {&draw_square ,&draw_rec ,& draw_circle ,&draw_poly };
typedef void (∗ fp )( struct shape∗ ps) drawfn ;
drawfn fp [4] = {&draw_square ,&draw_rec ,& draw_circle ,&draw_poly };

void draw ( struct shape∗ ps )
{
	(∗ fp [ps−>type ] ) ( ps ); / ∗ call the correct function ∗ /
}
```

