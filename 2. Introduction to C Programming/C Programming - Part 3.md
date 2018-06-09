# Pointers and Memory Address

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

​	***struct point p[3] = {{0,1}, {10,20}, {30,12}};**

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

