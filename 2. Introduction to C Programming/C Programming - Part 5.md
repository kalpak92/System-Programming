# [C Standard Library]()

## < stdio.h >

The **stdio.h** header defines three variable types, several macros, and various functions for performing input and output. 

### Library Variables

Following are the variable types defined in the header stdio.h

| Sr.No. | Variable & Description                                       |
| :----: | :----------------------------------------------------------- |
|   1    | **size_t**<br />This is the unsigned integral type and is the result of the **sizeof**keyword. |
|   2    | **FILE<br />**This is an object type suitable for storing information for a file stream. |
|   3    | **fpos_t<br />**This is an object type suitable for storing any position in a file. |

### Library Macros

Following are the macros defined in the header stdio.h

| Sr.No. | Macro & Description                                          |
| :----: | ------------------------------------------------------------ |
|   1    | **NULL**<br />This macro is the value of a null pointer constant. |
|   2    | **_IOFBF, _IOLBF** and **_IONBF**<br />These are the macros which expand to integral constant expressions with distinct values and suitable for the use as third argument to the **setvbuf** function. |
|   3    | **BUFSIZ**<br />This macro is an integer, which represents the size of the buffer used by the **setbuf** function. |
|   4    | **EOF**<br />This macro is a negative integer, which indicates that the end-of-file has been reached. |
|   5    | **FOPEN_MAX**<br />This macro is an integer, which represents the maximum number of files that the system can guarantee to be opened simultaneously. |
|   6    | **FILENAME_MAX**<br />This macro is an integer, which represents the longest length of a char array suitable for holding the longest possible filename. If the implementation imposes no limit, then this value should be the recommended maximum value. |
|   7    | **L_tmpnam**<br />This macro is an integer, which represents the longest length of a char array suitable for holding the longest possible temporary filename created by the **tmpnam** function. |
|   8    | **SEEK_CUR, SEEK_END,** and **SEEK_SET**<br />These macros are used in the **fseek** function to locate different positions in a file. |
|   9    | **TMP_MAX**<br />This macro is the maximum number of unique filenames that the function **tmpnam** can generate. |
|   10   | **stderr, stdin,** and **stdout**<br />These macros are pointers to FILE types which correspond to the standard error, standard input, and standard output streams. |

### Library Functions

#### Opening, closing files

**FILE∗ fopen(const char∗ filename,const char∗ mode)**

- mode can be "r"(read),"w"(write),"a"(append).
- "b" can be appended for binary input/output (unnecessary in *nx)
- returns NULL on error.

**FILE∗ freopen(const char∗ filename,const char∗ mode,FILE∗ stream)**

- redirects the stream to the file.
- returns NULL on error.
- Where can this be used? (redirecting stdin,stdout,stderr)

**int fflush (FILE∗ stream)**

- flushes any unwritten data.
- if stream is NULL flushes all outputs streams.
- returns EOF on error.

#### File operations

**int remove(const char∗ filename)**

- removes the file from the file system.
- return non-zero on error.

**int rename(const char∗ oldname,const char∗ newname)**

- renames file
- returns non-zero on error (reasons?: permission, existence)

#### Temporary files

**FILE∗ tmpfile(void)**

- creates a temporary file with mode "wb+".
- the file is removed automatically when program terminates.

**char∗ tmpnam(char s[L_tmpnam])**

- creates a string that is not the name of an existing file.
- return reference to internal static array if s is NULL. Populate `s` otherwise.
- generates a new name every call. 

#### Raw I/O

**size_t fread(void∗ ptr,size_t size,size_t nobj,FILE∗ stream)**

- reads at most `nobj` items of size `size` from stream into ptr.
- returns the number of items read.
- `feof` and `ferror` must be used to test end of file.

**size_t fwrite (const void∗ ptr,size_t size,size_t nobj,FILE∗ stream)**

- write at most `nobj` items of size `size` from `ptr` onto `stream`.
- returns number of objects written.

#### File position

**int fseek(FILE∗ stream, long offset,int origin )**

- sets file position in the stream. Subsequent read/write begins at this location
- origin can be `SEEK_SET, SEEK_CUR, SEEK_END`. 
- returns non-zero on error.

**long ftell (FILE∗ stream)**

- returns the current position within the file. (limitation? long data type).
- returns -1L on error.

**int rewind(FILE∗ stream)**

- sets the file pointer at the beginning.
- equivalent to fseek(`stream, 0L, SEEK_SET`); 

#### File errors

**void clearerr(FILE∗ stream)**

- clears EOF and other error indicators on stream.

**int feof(FILE∗ stream)**

- return non-zero (TRUE) if end of file indicator is set for stream.
- only way to test end of file for functions such as `fwrite(),fread()`

**int ferror (FILE∗ stream)**

- returns non-zero (TRUE) if any error indicator is set for stream.

## < ctype.h >

The **ctype.h** header file of the C Standard Library declares several functions that are useful for testing and mapping characters.

All the functions accepts **int** as a parameter, whose value must be EOF or representable as an unsigned char.

All the functions return non-zero (true) if the argument c satisfies the condition described, and zero(false) if not.

| Sr.No. | Function & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | [int isalnum(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isalnum.htm)<br />This function checks whether the passed character is alphanumeric. |
|   2    | [int isalpha(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isalpha.htm)<br />This function checks whether the passed character is alphabetic. |
|   3    | [int iscntrl(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_iscntrl.htm)<br />This function checks whether the passed character is control character. |
|   4    | [int isdigit(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isdigit.htm)<br />This function checks whether the passed character is decimal digit. |
|   5    | [int isgraph(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isgraph.htm)<br />This function checks whether the passed character has graphical representation using locale. |
|   6    | [int islower(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_islower.htm)<br />This function checks whether the passed character is lowercase letter. |
|   7    | [int isprint(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isprint.htm)<br />This function checks whether the passed character is printable. |
|   8    | [int ispunct(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_ispunct.htm)<br />This function checks whether the passed character is a punctuation character. |
|   9    | [int isspace(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isspace.htm)<br />This function checks whether the passed character is white-space. |
|   10   | [int isupper(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isupper.htm)<br />This function checks whether the passed character is an uppercase letter. |
|   11   | [int isxdigit(int c)](https://www.tutorialspoint.com/c_standard_library/c_function_isxdigit.htm)<br />This function checks whether the passed character is a hexadecimal digit. |

## < string.h >

The **string.h** header defines one variable type, one macro, and various functions for manipulating arrays of characters. 

### Library Variables

Following is the variable type defined in the header string.h

| Sr.No. | Variable & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **size_t**<br />This is the unsigned integral type and is the result of the **sizeof** keyword. |

### Library Macros

Following is the macro defined in the header string.h

| Sr.No. | Macro & Description                                          |
| :----: | ------------------------------------------------------------ |
|   1    | **NULL**<br />This macro is the value of a null pointer constant. |

### Library Functions

Following are the functions defined in the header string.h −

| Sr.No. | Function & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | [void *memchr(const void *str, int c, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_memchr.htm)<br />Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to, by the argument *str*. |
|   2    | [int memcmp(const void *str1, const void *str2, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_memcmp.htm)<br />Compares the first n bytes of *str1* and *str2*. |
|   3    | [void *memcpy(void *dest, const void *src, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm)<br />Copies n characters from src to *dest*. |
|   4    | [void *memmove(void *dest, const void *src, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_memmove.htm)<br />Another function to copy n characters from *str2* to *str1*. |
|   5    | [void *memset(void *str, int c, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_memset.htm)<br />Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument *str*. |
|   6    | [char *strcat(char *dest, const char *src)](https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm)<br />Appends the string pointed to, by *src* to the end of the string pointed to by *dest*. |
|   7    | [char *strncat(char *dest, const char *src, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_strncat.htm)<br />Appends the string pointed to, by *src* to the end of the string pointed to, by *dest* up to n characters long. |
|   8    | [char *strchr(const char *str, int c)](https://www.tutorialspoint.com/c_standard_library/c_function_strchr.htm)<br />Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument *str*. |
|   9    | [int strcmp(const char *str1, const char *str2)](https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm)<br />Compares the string pointed to, by *str1* to the string pointed to by *str2*. |
|   10   | [int strncmp(const char *str1, const char *str2, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_strncmp.htm)<br />Compares at most the first n bytes of *str1* and *str2*. |
|   11   | [int strcoll(const char *str1, const char *str2)](https://www.tutorialspoint.com/c_standard_library/c_function_strcoll.htm)<br />Compares string *str1* to *str2*. The result is dependent on the LC_COLLATE setting of the location. |
|   12   | [char *strcpy(char *dest, const char *src)](https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm)<br />Copies the string pointed to, by *src* to *dest*. |
|   13   | [char *strncpy(char *dest, const char *src, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_strncpy.htm)<br />Copies up to n characters from the string pointed to, by *src* to *dest*. |
|   14   | [size_t strcspn(const char *str1, const char *str2)](https://www.tutorialspoint.com/c_standard_library/c_function_strcspn.htm)<br />Calculates the length of the initial segment of str1 which consists entirely of characters not in str2. |
|   15   | [char *strerror(int errnum)](https://www.tutorialspoint.com/c_standard_library/c_function_strerror.htm)<br />Searches an internal array for the error number errnum and returns a pointer to an error message string. |
|   16   | [size_t strlen(const char *str)](https://www.tutorialspoint.com/c_standard_library/c_function_strlen.htm)<br />Computes the length of the string str up to but not including the terminating null character. |
|   17   | [char *strpbrk(const char *str1, const char *str2)](https://www.tutorialspoint.com/c_standard_library/c_function_strpbrk.htm)<br />Finds the first character in the string *str1* that matches any character specified in *str2*. |
|   18   | [char *strrchr(const char *str, int c)](https://www.tutorialspoint.com/c_standard_library/c_function_strrchr.htm)<br />Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument *str*. |
|   19   | [size_t strspn(const char *str1, const char *str2)](https://www.tutorialspoint.com/c_standard_library/c_function_strspn.htm)<br />Calculates the length of the initial segment of *str1* which consists entirely of characters in *str2*. |
|   20   | [char *strstr(const char *haystack, const char *needle)](https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm)<br />Finds the first occurrence of the entire string *needle* (not including the terminating null character) which appears in the string *haystack*. |
|   21   | [char *strtok(char *str, const char *delim)](https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm)<br />Breaks string *str* into a series of tokens separated by *delim*. |
|   22   | [size_t strxfrm(char *dest, const char *src, size_t n)](https://www.tutorialspoint.com/c_standard_library/c_function_strxfrm.htm)<br />Transforms the first **n** characters of the string **src** into current locale and places them in the string **dest**. |

**What is the difference between memmove and memcpy?**

With `memcpy`, the destination cannot overlap the source at all. With `memmove` it can. This means that `memmove` might be very slightly slower than `memcpy`, as it cannot make the same assumptions.

For example, `memcpy` might always copy addresses from low to high. If the destination overlaps after the source, this means some addresses will be overwritten before copied. `memmove` would detect this and copy in the other direction - from high to low - in this case. However, checking this and switching to another (possibly less efficient) algorithm takes time.

Consider

```c
char[] str = "foo-bar";
memcpy(&str[3],&str[4],4); //might blow up
```

Obviously the source and destination now overlap, we're overwriting "-bar" with "bar". It's undefined behavior using `memcpy` if the source and destination overlap so in this case cases we need `memmove`.

```c
memmove(&str[3],&str[4],4); //fine
```

**What is the difference between memset and memcpy in C ?**

`memcpy()` copies from one place to another. `memset()` just sets all pieces of memory to the same value.

Example:

```c
memset(str, '*', 50);   
```

The above line sets the first 50 characters of the string str to * (or whatever second argument of the memset).

```c
memcpy(str2, str1, 50); 
```

The above line copies the first 50 characters of str1 to str2.

```c
char a[4];
memset(a, 7, sizeof(char)*4);
/*
* a is now...
*
* +-+-+-+-+
* |7|7|7|7|
* +-+-+-+-+
*/

char b[] = {1,2,3,4};
char c[4];
memcpy(c, b, sizeof(char)*4);
/*
* c is now...
*
* +-+-+-+-+
* |1|2|3|4|
* +-+-+-+-+
*/
```

**What is the difference between memcmp, strcmp and strncmp in C?**

 In short:

- [`strcmp`](http://linux.die.net/man/3/strcmp) compares null-terminated C strings
- [`strncmp`](http://linux.die.net/man/3/strcmp) compares at most N characters of null-terminated C strings
- [`memcmp`](http://linux.die.net/man/3/memcmp) compares binary byte buffers of N bytes. This function is used compare two variables using their memory. It doesn't compare them one by one, It compares four characters at one time. If your program is too concerned about speed, I recommend using memcmp().

So, if you have these strings:

```c
const char s1[] = "atoms\0\0\0\0";  // extra null bytes at end
const char s2[] = "atoms\0abc";     // embedded null byte
const char s3[] = "atomsaaa";
```

Then these results hold true:

```c
strcmp(s1, s2) == 0      // strcmp stops at null terminator
strcmp(s1, s3) != 0      // Strings are different
strncmp(s1, s3, 5) == 0  // First 5 characters of strings are the same
memcmp(s1, s3, 5) == 0   // First 5 bytes are the same
strncmp(s1, s2, 8) == 0  // Strings are the same up through the null terminator
memcmp(s1, s2, 8) != 0   // First 8 bytes are different
```

## < stdlib.h >

The **stdlib.h** header defines four variable types, several macros, and various functions for performing general functions. 

### Library Variables

Following are the variable types defined in the header stdlib.h −

| Sr.No. | Variable & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **size_t**<br />This is the unsigned integral type and is the result of the **sizeof**keyword. |
|   2    | **wchar_t**<br />This is an integer type of the size of a **wide** character constant. |
|   3    | **div_t**<br />This is the structure returned by the **div** function. |
|   4    | **ldiv_t**<br />This is the structure returned by the **ldiv** function. |

### Library Macros

Following are the macros defined in the header stdlib.h −

| Sr.No. | Macro & Description                                          |
| :----: | :----------------------------------------------------------- |
|   1    | **NULL**<br />This macro is the value of a null pointer constant. |
|   2    | **EXIT_FAILURE**<br />This is the value for the exit function to return in case of failure. |
|   3    | **EXIT_SUCCESS**<br />This is the value for the exit function to return in case of success. |
|   4    | **RAND_MAX**<br />This macro is the maximum value returned by the rand function. |
|   5    | **MB_CUR_MAX**<br />This macro is the maximum number of bytes in a multi-byte character set which cannot be larger than MB_LEN_MAX. |

### Library Functions

Following are the functions defined in the header stdio.h −

| Sr.No. | Function & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **double atof(const char *str)**<br />Converts the string pointed to, by the argument *str* to a floating-point number (type double). |
|   2    | **int atoi(const char *str)**<br />Converts the string pointed to, by the argument *str* to an integer (type int). |
|   3    | **long int atol(const char *str)**<br />Converts the string pointed to, by the argument *str* to a long integer (type long int). |
|   4    | **void *calloc(size_t nitems, size_t size)**<br />Allocates the requested memory and returns a pointer to it. |
|   5    | **void free(void *ptr)**<br />Deallocates the memory previously allocated by a call to *calloc, malloc,* or *realloc*. |
|   6    | **void *malloc(size_t size)**<br />Allocates the requested memory and returns a pointer to it. |
|   7    | **void *realloc(void *ptr, size_t size)**<br />Attempts to resize the memory block pointed to by ptr that was previously allocated with a call to *malloc* or *calloc*. |

**int rand()**

- returns a pseduo-random numbers between 0 and RAND_MAX

**void srand(unsigned int seed)**

- sets the seed for the pseudo-random generator! 

**void abort(void)**

- causes the program to terminate abnormally.

**void exit (int status)**

- causes normal program termination. The value status is returned to the operating system.
- 0 EXIT_SUCCESS indicates successful termination. Any other value indicates failure (EXIT_FAILURE)

**void atexit (void (∗fcn)(void))**

- registers a function fcn to be called when the program terminates normally;
- returns non zero when registration cannot be made.
- After exit() is called, the functions are called in reverse order of registration.

**int system(const char∗ cmd)**

- executes the command in string cmd.
- if cmd is not null, the program executes the command and returns exit status returned by the command.

**void bsearch ( const void key , const ∗ ∗ void∗ base , size _t n, size _t size , int (∗cmp ) ( const void∗ keyval , const void∗ datum ) ) ;**

- searches base[0] through base[n-1] for * key.
- function cmp() is used to perform comparison.
- returns a pointer to the matching item if it exists and NULL otherwise.

**void qsort ( void∗ base , size _t n, size _t sz , int (∗cmp ) ( const void ∗ , const void ∗ ))**

- sorts base[0] through base[n-1] in ascending/descending order.
- function cmp() is used to perform comparison.

## < assert.h >

The **assert.h** header file of the C Standard Library provides a macro called **assert** which can be used to verify assumptions made by the program and print a diagnostic message if this assumption is false.

The defined macro **assert** refers to another macro **NDEBUG** which is not a part of <assert.h>. If NDEBUG is defined as a macro name in the source file, at the point where <assert.h> is included, the **assert** macro is defined as follows −

```c
#define assert(ignore) ((void)0)
```

### Library Macros

Following is the only function defined in the header assert.h −

| Sr.No. | Function & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **void assert(int expression)**<br />This is actually a macro and not a function, which can be used to add diagnostics in your C program. |

## < stdarg.h >

The **stdarg.h** header defines a variable type **va_list** and three macros which can be used to get the arguments in a function when the number of arguments are not known i.e. variable number of arguments.

A function of variable arguments is defined with the **ellipsis (,...)** at the end of the parameter list.

### Library Variables

Following is the variable type defined in the header stdarg.h −

| Sr.No. | Variable & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **va_list**<br />This is a type suitable for holding information needed by the three macros **va_start(), va_arg()** and **va_end()**. |

### Library Macros

Following are the macros defined in the header stdarg.h −

| Sr.No. | Macro & Description                                          |
| :----: | ------------------------------------------------------------ |
|   1    | **void va_start(va_list ap, last_arg)**<br />This macro initializes **ap** variable to be used with the **va_arg** and **va_end** macros. The **last_arg** is the last known fixed argument being passed to the function i.e. the argument before the ellipsis. |
|   2    | **type va_arg(va_list ap, type)**<br />This macro retrieves the next argument in the parameter list of the function with type **type**. |
|   3    | **void va_end(va_list ap)**<br />This macro allows a function with variable arguments which used the **va_start** macro to return. If **va_end** is not called before returning from the function, the result is undefined. |

### Variable argument lists

- functions can have variable number of arguments.
- the data type of the argument can be different for each argument.
- atleast one mandatory argument is required.

Declaration:

```c
int printf (char∗ fmt ,...); /∗fmt is last named argument∗/
```

#### va_list ap

- ap defines an iterator that will point to the variable argument.
- Before using, it has to be initialized using **va_start**. 

#### va_start()

The C library macro **void va_start(va_list ap, last_arg)** initializes **ap **variable to be used with the **va_arg** and **va_end** macros. The **last_arg** is the last known fixed argument being passed to the function i.e. the argument before the ellipsis.

This macro must be called before using **va_arg** and **va_end**.

Following is the declaration for va_start() macro.

```c
void va_start(va_list ap, last_arg);
```

- **ap** − This is the object of **va_list** and it will hold the information needed to retrieve the additional arguments with **va_arg**.
- **last_arg** − This is the last known fixed argument being passed to the function.

#### va_arg()

The C library macro **type va_arg(va_list ap, type)** retrieves the next argument in the parameter list of the function with **type**. This does not determine whether the retrieved argument is the last argument passed to the function. 

Following is the declaration for va_arg() macro.

```c
type va_arg(va_list ap, type)
```

- **ap** − This is the object of type va_list with information about the additional arguments and their retrieval state. This object should be initialized by an initial call to va_start before the first call to va_arg.
- **type** − This is a type name. This type name is used as the type of the expression, this macro expands to.

**Return Value**

​	This macro returns the next additional argument as an expression of type **type**.

#### va_end()

The C library macro **void va_end(va_list ap)** allows a function with variable arguments which used the **va_start** macro to return. If **va_end** is not called before returning from the function, the result is undefined. 

Following is the declaration for va_end() macro.

```c
void va_end(va_list ap)
```

- **ap** − This is the va_list object previously initialized by va_start in the same function. 

```c
#include<stdarg.h>
#include<stdio.h>

int sum(int, ...);

int main(void) {
   printf("Sum of 10, 20 and 30 = %d\n",  sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  sum(4, 4, 20, 25, 30) );

   return 0;
}

int sum(int num_args, ...) {
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}
```

Let us compile and run the above program to produce the following result −

```shell
Sum of 10, 20 and 30 = 60
Sum of 4, 20, 25 and 30 = 79
```

# < time.h >

The **time.h** header defines four variable types, two macro and various functions for manipulating date and time.

###  Library Variables

Following are the variable types defined in the header time.h −

| Sr.No. | Variable & Description                                       |
| :----: | ------------------------------------------------------------ |
|   1    | **size_t** This is the unsigned integral type and is the result of the **sizeof** keyword. |
|   2    | **clock_t** This is a type suitable for storing the processor time. |
|   3    | **time_t is** This is a type suitable for storing the calendar time. |
|   4    | **struct tm** This is a structure used to hold the time and date. |

The tm structure has the following definition −

```c
struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */
};
```

### Library Functions

#### clock_t clock(void)

Returns the processor clock time used since the beginning of an implementation defined era (normally the beginning of the program).

The C library function **clock_t clock(void)** returns the number of clock ticks elapsed since the program was launched. To get the number of seconds used by the CPU, you will need to divide by CLOCKS_PER_SEC.

On a 32 bit system where CLOCKS_PER_SEC equals 1000000 this function will return the same value approximately every 72 minutes.

```c
#include <time.h>
#include <stdio.h>

int main () {
   clock_t start_t, end_t, total_t;
   int i;

   start_t = clock();
   printf("Starting of the program, start_t = %ld\n", start_t);
    
   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   for(i=0; i< 10000000; i++) {
   }
   end_t = clock();
   printf("End of the big loop, end_t = %ld\n", end_t);
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %f\n", total_t  );
   printf("Exiting of the program...\n");

   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Starting of the program, start_t = 0
Going to scan a big loop, start_t = 0
End of the big loop, end_t = 20000
Total time taken by CPU: 0.000000
Exiting of the program...
```

#### **time_t time(time_t \*seconds)** 

The C library function **time_t time(time_t \*seconds)** returns the time since the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds. If **seconds** is not NULL, the return value is also stored in variable **seconds**. 

Following is the declaration for time() function.

```
time_t time(time_t *t)
```

**Parameters**

- **seconds** − This is the pointer to an object of type time_t, where the seconds value will be stored.

returns current time (seconds since Jan 1 1970).

if tp is not NULL, also populates tp. 

```c
#include <stdio.h>
#include <time.h>

int main () {
   time_t seconds;

   seconds = time(NULL);
   printf("Hours since January 1, 1970 = %ld\n", seconds/3600);
  
   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Hours since January 1, 1970 = 393923
```

#### difftime()

The C library function **double difftime(time_t time1, time_t time2)**returns the difference of seconds between **time1** and **time2** i.e. **(time1 - time2)**. The two times are specified in calendar time, which represents the time elapsed since the Epoch (00:00:00 on January 1, 1970, Coordinated Universal Time (UTC)).

**Declaration**

Following is the declaration for difftime() function.

```
double difftime(time_t time1, time_t time2)
```

**Parameters**

- **time1** − This is the time_t object for end time.
- **time2** − This is the time_t object for start time.

**Return Value**

This function returns the difference of two times (time1 - time2) as a double value.

```c
#include <stdio.h>
#include <time.h>

int main () {
   time_t start_t, end_t;
   double diff_t;

   printf("Starting of the program...\n");
   time(&start_t);

   printf("Sleeping for 5 seconds...\n");
   sleep(5);

   time(&end_t);
   diff_t = difftime(end_t, start_t);

   printf("Execution time = %f\n", diff_t);
   printf("Exiting of the program...\n");

   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Starting of the program...
Sleeping for 5 seconds...
Execution time = 5.000000
Exiting of the program...
```

#### **time_t mktime(struct tm \*timeptr)** 

The C library function **time_t mktime(struct tm \*timeptr)** converts the structure pointed to by **timeptr** into a time_t value according to the local time zone. 

Following is the declaration for mktime() function.

```
time_t mktime(struct tm *timeptr)
```

**Parameters**

- **timeptr** − This is the pointer to a time_t value representing a calendar time, broken down into its components. Below is the detail of timeptr structure

```c
struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */	
};
```

**Return Value**

This function returns a time_t value corresponding to the calendar time passed as argument. On error, a -1 value is returned.

```c
#include <stdio.h>
#include <time.h>

int main () {
   int ret;
   struct tm info;
   char buffer[80];

   info.tm_year = 2001 - 1900;
   info.tm_mon = 7 - 1;
   info.tm_mday = 4;
   info.tm_hour = 0;
   info.tm_min = 0;
   info.tm_sec = 1;
   info.tm_isdst = -1;

   ret = mktime(&info);
   if( ret == -1 ) {
      printf("Error: unable to make time using mktime\n");
   } else {
      strftime(buffer, sizeof(buffer), "%c", &info );
      printf(buffer);
   }

   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Wed Jul 4 00:00:01 2001
```

#### **char \*asctime(const struct tm *timeptr)** 

The C library function **char \*asctime(const struct tm *timeptr)** returns a pointer to a string which represents the day and time of the structure **struct timeptr**. 

Following is the declaration for asctime() function.

```c
char *asctime(const struct tm *timeptr)
```

The **timeptr** is a pointer to tm structure that contains a calendar time broken down into its components.

This function returns a C string containing the date and time information in a human-readable format **Www Mmm dd hh:mm:ss yyyy**, where *Www* is the weekday, *Mmm* the month in letters, *dd* the day of the month, *hh:mm:ss* the time, and *yyyy* the year. 

The following example shows the usage of asctime() function.

```c
#include <stdio.h>
#include <string.h>
#include <time.h>

int main () {
   struct tm t;

   t.tm_sec    = 10;
   t.tm_min    = 10;
   t.tm_hour   = 6;
   t.tm_mday   = 25;
   t.tm_mon    = 2;
   t.tm_year   = 89;
   t.tm_wday   = 6;

   puts(asctime(&t));
   
   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Sat Mar 25 06:10:10 1989
```

#### **struct tm \*localtime(const time_t *timer)** 

The C library function **struct tm \*localtime(const time_t *timer)** uses the time pointed by **timer** to fill a **tm** structure with the values that represent the corresponding local time. The value of **timer** is broken up into the structure **tm** and expressed in the local time zone. 

Following is the declaration for localtime() function.

```
struct tm *localtime(const time_t *timer)
```

**Parameters**

- **timer** − This is the pointer to a time_t value representing a calendar time.

**Return Value**

This function returns a pointer to a **tm** structure with the time information filled in.

```c
#include <stdio.h>
#include <time.h>

int main () {
   time_t rawtime;
   struct tm *info;
   char buffer[80];

   time( &rawtime );

   info = localtime( &rawtime );
   printf("Current local time and date: %s", asctime(info));

   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Current local time and date: Thu Aug 23 09:12:05 2012
```

#### **char \*ctime(const time_t *timer)** 

The C library function **char \*ctime(const time_t *timer)** returns a string representing the localtime based on the argument **timer**.

The returned string has the following format: **Www Mmm dd hh:mm:ss yyyy**, where *Www* is the weekday, *Mmm* the month in letters, *dd* the day of the month, *hh:mm:ss* the time, and *yyyy* the year.

Following is the declaration for ctime() function.

```
char *ctime(const time_t *timer)
```

**Parameters**

- **timer** − This is the pointer to a time_t object that contains a calendar time.

**Return Value**

This function returns a C string containing the date and time information in a human-readable format.

```c
#include <stdio.h>
#include <time.h>

int main () {
   time_t curtime;

   time(&curtime);

   printf("Current time = %s", ctime(&curtime));

   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Current time = Mon Aug 13 08:23:14 2012
```

#### strftime()

 The C library function **size_t strftime(char \*str, size_t maxsize, const char *format, const struct tm *timeptr)** formats the time represented in the structure **timeptr** according to the formatting rules defined in **format** and stored into **str**. 

Following is the declaration for strftime() function.

```c
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
```

**Parameters**

- **str** − This is the pointer to the destination array where the resulting C string is copied.
- **maxsize** − This is the maximum number of characters to be copied to str.
- **format** − This is the C string containing any combination of regular characters and special format specifiers. These format specifiers are replaced by the function to the corresponding values to represent the time specified in tm. The format specifiers are −

```c
#include <stdio.h>
#include <time.h>

int main () {
   time_t rawtime;
   struct tm *info;
   char buffer[80];

   time( &rawtime );

   info = localtime( &rawtime );

   strftime(buffer,80,"%x - %I:%M%p", info);
   printf("Formatted date & time : |%s|\n", buffer );
  
   return(0);
}
```

Let us compile and run the above program that will produce the following result −

```shell
Formatted date & time : |08/23/12 - 12:40AM|
```

