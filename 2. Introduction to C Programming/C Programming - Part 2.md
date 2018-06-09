# C Programming: Part 2

## Control Flow

- Unlike C++ or Java, no boolean type (in C89/C90)
  - in C99, bool type available (use ***stdbool.h***)
- Condition is an expression (or series of expressions)
  	e.g. ***n<3 or x<y || z<y***
- Expression is non-zero => condition true
- Expression must be numeric (or a pointer)

```c
const char str[] = "some text" ;
if (str) / ∗ string is not null ∗ /
return 0;
```

## Conditional statements

### The if statement

```c
if (x% 2) 
	y += x/2;
```

Evaluate condition

​	if (x %2==0)

If true, evaluate inner statement 

​	y += x/2;

Otherwise, do nothing

### The else keyword

```c
if (x%2 == 0) 
	y += x/2;
else
	y += (x+1)/2;
```

- Optional 
- Execute statement if condition is false
  	y += (x+1)/2;
- Either inner statement may be block

### The else if keyword

```c
if (x%2 == 0) 
	y += x/2; 
else if (x%4 == 1)
	 y+= 2∗ ((x+3)/4);
else
	y += (x+1)/2;
```

- Additional alternative control paths
- Conditions evaluated in order until one is met; inner statement then executed
- If multiple conditions true, only first executed
- Equivalent to nested if statements3

### Nesting if statements

```c
if (x%4 == 0) 
	if (x%2 == 0) 
    y= 2;
else
	y= 1;
```

To which if statement does the else keyword belong?

To associate else with outer if statement: use braces

```c
if (x%4 == 0) 
{ 
	if (x%2 == 0) 
	y= 2; 
}
else 
	y= 1;
```

### The switch statement

- Alternative conditional statement
- Integer (or character) variable as input
- Considers cases for value of variable

```c
switch (ch) {
case ’Y’ :/ ∗ ch == ’Y’ ∗ /
/ ∗ do something ∗ /
break ; case ’N’ :/ ∗ ch == ’N’ ∗ / / ∗ do something else ∗ /
break ;
default :/ ∗ otherwise ∗ /
/ ∗ do a third thing ∗ /
break ;
}
```

- Compares variable to each case in order
- When match found, starts executing inner code until break; reached
- Execution “falls through” if break; not included


- Contents of switch statement a block
- Case labels: different entry points into block
- Similar to labels used with goto keyword

## Loop statements

- The while loop
  	while (/ ∗ condition ∗ /) 
  	/ ∗ loop body ∗ /

  - Simplest loop structure – evaluate body as long as condition is true.
  - Condition evaluated first, so body may never be executed

- The for loop

  - The “counting” loop

  - Inside parentheses, three expressions, separated by semicolons:

    - Initialization: i=1
    - Condition: i <= n
    - Increment: i++

  -  Expressions can be empty (condition assumed to be “true”)

  - ```c
    int factorial ( int n) 
    { 
        int j =1; int i=1; / ∗ initialization ∗ / 
        while (i <= n/ ∗ condition ∗ /) 
        {
    		j ∗= i;
    		i ++; / ∗ increment ∗ /
    	}
    	return j;
    }
    ```


  - Compound expressions separated by commas

    ```c
    int factorial ( int n) 
    {
    	int i, j;
    	for (i =1, j=1; i<= n; j ∗= i , i++);
    	return j;
    }
    ```


  - Comma: operator with lowest precedence, evaluated left-to-right; not same as between function arguments

- The do-while loop

  - Differs from while loop – condition evaluated after each iteration

  - Body executed at least once

  - Note semicolon at end

  - ```c
    char c; 
    do {
    / ∗ loop body ∗ /
    puts ( "Keep going? (y/n) " );
    c = getchar ( ) ;
    / ∗ other processing ∗ / 
    } while (c == ’y’ && / ∗ other conditions ∗ / );
    ```


- The break and continue keywords

  - Sometimes want to terminate a loop early
  - break; exits innermost loop or switch statement to exit early


  - continue; skips rest of innermost loop body, jumping to loop condition

## Modular Programming in C

- C programs do not need to be monolithic
- Module: interface and implementation 
  - interface: header files
  - implementation: auxilliary source/object files

### How does Modularity help ?

- Decompose execution into modules
  - Read strings
  - Sort strings
  - Write strings
- Interfaces hide details
  - Localize effect of changes
- Why is this better?
  - Easier to understand
  - Easier to test and debug
  - Easier to reuse code
  - Easier to make

### The extern keyword

- Need to inform other source files about functions/global variables in .c files.
- For functions: ***put function prototypes in a header file***
- For variables: ***re-declare the global variable using the extern keyword in header file***
- extern informs compiler that variable defined somewhere else
- Enables access/modifying of global variable from other source files

### Question

We are writing a simple searchable dictionary using modular programming. First, the program reads a file containing words and their definitions into an easily searchable data structure. Then, the user can type a word, and the program will search the dictionary, and assuming the word is found, outputs the definition. The program proceeds until the user chooses to quit. 

We split the code into several files: main.c, dict.c, and dict.h. The contents of these files are described briefly below. 

main.c: 

![Modular programming q1](https://github.com/kalpak92/System-Programming/blob/master/2.%20Introduction%20to%20C%20Programming/Modular%20programming%20q1.PNG)

1. In implementing this program, you want to access the global variable the dictionary from main.c, as well as from dict.c. However, due to the header file’s inclusion in both source documents, the variable gets declared in both places, creating an ambiguity. How would you resolve this ambiguity?

   Answer: Adding the **extern keyword** immediately before the declaration in dict.h resolves the ambiguity, causing both files to reference the variable declared in dict.c.

2. Now, suppose you want to restrict the dictionary data structure to be accessible only from functions in dict.c. You remove the declaration from dict.h. Is it still possible to directly access or modify the variable from main.c, even without the declaration in dict.h? If so, how would you ensure the data structure variable remains private? 

   Answer: Simply removing the declaration from dict.h does not make the variable private to dict.c. One could simply add an extern declaration to main.c or any other source file and still be able to access or modify the dictionary directly. In order to prevent direct access, **the dictionary should be declared with the static keyword in dict.c.** 

3. Congratulations! You’re done and ready to compile your code. Write the command line that you should use to compile this code (using gcc). Let’s call the desired output program dictionary.o. 

   Answer: **gcc -g -O0 -Wall main.c dict.c -o dictionary.o.** 

   Note that the order of main.c and dict.c is not important, as long as they are both specified. 

## Variable scope

- *scope* – the region in which a variable is valid.
- Many cases, corresponds to block with variable’s declaration.
- Variables declared outside of a function have global scope.
- Function definitions also have scope

#### Static Variables

- static keyword has two meanings, depending on where the static variable is declared
- Outside a function, static variables/functions only visible within that file, not globally (cannot be extern’ed)
- Inside a function, static variables:
  - are still local to that function
  - are initialized only during program initialization
  - do not get reinitialized with each function call

#### Register variables

- During execution, data processed in registers.
- Explicitly store commonly used data in registers – minimize load/store overhead
- Can explicitly declare certain variables as registers using register keyword
  - must be a simple type (implementation-dependent) • only local variables and function arguments eligible
  - excess/unallowed register declarations ignored, compiled as regular variables
- Registers do not reside in addressed memory 
  - pointer of a register variable illegal

```c
int main ( register int argc , register char **argv )
{ 
	register int a=0, b=1, c, n, nmax =20;
    printf ( "%3d: %d\n" ,1 ,a ); 
    printf ( "%3d: %d\n" ,2 ,b ); 
    
    for (n =3; n<= nmax; n++) {
		c=a+b; a=b; b=c;
		printf ( "%3d: %d\n" ,n, c );
	}
	return 0; / ∗ success ∗ /
}
```

## I/O

- Input and output facilities are provided by the standard library <stdio.h> and not by the language itself.

- A text stream consists of a series of lines ending with ’\n’ .

  The standard library takes care of conversion from ’\r\n’−’\n’

- A binary stream consists of a series of raw bytes.

- The streams provided by standard library are **buffered**.

### Standard input and output

#### int putchar(int)

- putchar(c) puts the character c on the standard output.
- it returns the character printed or EOF on error.

#### int getchar()

- returns the next character from standard input.
- it returns EOF on error.

```c
int main ()
{
	char c ;
	while (( c=getchar ())!= EOF)
	{
		if ( c>=’A’ && c<=’Z’ )
			c=c−’A’+’a’ ;
	putchar (c );
	}
	return 0;
}
```

#### Standard output: formatted

```c
int printf (char format[],arg1,arg2 ,...)
```

- printf() can be used for formatted output.
- It takes in a variable number of arguments.
- It returns the number of characters printed.
- The format can contain literal strings as well as format specifiers (starts with %).

Examples:

```c
printf ( "hello world\n" );
printf ( "%d\n" ,10); 	/ ∗ format : %d ( integer ) , argument:10 ∗ /
printf ( "Prices:%d and %d\n" ,10 ,20);
```

##### printf format specification

The format specification has the following components
	%\[ flags ]\[ width ]\[. precision]\[ length] \<type>

**type:**

| Type |     Meaning      | Example                               |
| :--: | :--------------: | :------------------------------------ |
| d, i |     integer      | printf(“%d”, 10);                     |
| X, x |  integer (hex)   | printf(“%x”, 10);     /* print 0xa */ |
|  u   | unsigned integer | printf(“%u”, 10);                     |
|  c   |    character     | printf(“%c”, ‘A’);                    |
|  s   |      string      | printf(“%s”, “hello”);                |
|  f   |      float       | printf(“%f”, 2.3);                    |
|  d   |      double      | printf(“%d”, 2.3);                    |
| E, e |    float(exp)    | 1e3,1.2E3,1E−3                        |
|  %   |    literal %     | printf ("%d %%",10); /∗prints 10%∗/   |

% \[flags]\[width ]\[. precision]\[modifier] \<type>
**width**:

| Format                   | Output         |
| ------------------------ | -------------- |
| print(“%d”, 10);         | 10             |
| printf(“%4d”, 10);       | bb10 (b:space) |
| printf   ("%s","hello")  | hello          |
| printf   ("%7s","hello") | bbhello        |

%\[flags]\[width ]\[. precision]\[modifier]\<type>

**flag:**

| Format                         | Output     |
| ------------------------------ | ---------- |
| printf   ("%d,%+d,%+d",10,−10) | 10,+10,-10 |
| printf   ("%04d",10)           | 0010       |
| printf   ("%7s","hello")       | bbhello    |
| printf   ("%-7s","hello")      | hellobb    |

%\[flags]\[width ]\[. precision]\[modifier]\<type>

**precision :**

| Format                             | Output         |
| ---------------------------------- | -------------- |
| printf   ("%.2f,%.0f,1.141,1.141)  | 1.14,1         |
| printf   ("%.2e,%.0e,1.141,100.00) | 1.14e+00,1e+02 |
| printf   ("%.4s","hello")          | hell           |
| printf   ("%.1s","hello")          | h              |

%\[flags]\[width ]\[. precision]\[modifier]\<type>

**modifier:**

| modified | meaning            |
| -------- | ------------------ |
| h        | use with i,d,o,u,x |
| i        | use with i,d,o,u,x |
| l        | use with i,d,o,u,x |

#### Character Arrays

- strings are represented as an array of characters
- C does not restrict the length of the string. The end of the string is specified using 0.

For instance, "hello" is represented using the array **{’h’,’e’,’l’,’l’,’\0’}** .
Declaration examples:

- **char str []="hello";** /∗compiler takes care of size∗/

- **char str[10]="hello";** /∗make sure the array is large enough∗/

- **char str []={ ’h’,’e’,’l’,’l’,0};**

  Note: use \" if you want the string to contain ".

Comparing strings: the header file <string.h> provides the function `int strcmp(char s[],char t [])` that compares two strings in dictionary order (lower case letters come after capital case).

- the function returns a value <0 if s comes before t
- the function return a value 0 if s is the same as t
- the function return a value >0 if s comes after t
- strcmp is case sensitive

Examples

- **strcmp("A","a")** /∗<0∗/
- **strcmp("IRONMAN","BATMAN")**  /∗>0∗/
- **strcmp("aA","aA")** /∗==0∗/
- **strcmp("aA","a")** /∗>0∗/

#### Formatted input

`int scanf(char∗ format ,...)` is the input analog of printf.

- scanf reads characters from standard input, interpreting them according to format specification
- Similar to printf , scanf also takes variable number of arguments.
- The format specification is the same as that for printf
- When multiple items are to be read, each item is assumed to be separated by white space.
- **It returns the number of items read or EOF**.
- Important: **scanf ignores white spaces**.
- Important: Arguments have to be **address of variables (pointers)**.

Examples:

|            printf            |                  scanf                   |
| :--------------------------: | :--------------------------------------: |
|       printf ("%d",x)        |              scanf("%d",&x)              |
|      printf ("%10d",x)       |              scanf("%d",&x)              |
|       printf ("%f",f)        |              scanf("%f",&f)              |
|      printf ("%s",str)       |  scanf("%s",str) /∗note no & required∗/  |
|      printf ("%s",str)       | scanf("%20s",str) /∗note no & required∗/ |
| printf ("%s %s",fname,lname) |      scanf("%20s %20s",fname,lname)      |

## String input/output

Instead of writing to the standard output, the formatted data can be written to or read from character arrays.
**int sprintf (char string [], char format[],arg1,arg2)**

- The format specification is the same as printf.
- The output is written to string (does not check size).
- Returns the number of character written or negative value on error.

**int sscanf(char str [], char format[],arg1,arg2)**

- The format specification is the same as scanf;
- The input is read from str variable.
- Returns the number of items read or negative value on error.

## File I/O

So far, we have read from the standard input and written to the standard output. C allows us to read data from text/binary files using fopen() .

**FILE∗ fopen(char name[],char mode[])**

- mode can be "r" (read only),"w" (write only),"a" (append) among other options. "b" can be appended for binary files.
- fopen returns a **pointer** to the file stream if it exists or NULL otherwise.
- We don’t need to know the details of the FILE data type.
- **Important**: The standard input and output are also FILE* datatypes (stdin,stdout).
- **Important**: stderr corresponds to standard error output(different from stdout).

**int fclose(FILE∗ fp)**

- closes the stream (releases OS resources).
- fclose() is automatically called on all open files when program terminates.

### File input

**int getc(FILE∗ fp)**

- reads a single character from the stream.
- returns the character read or EOF on error/end of file.

Note: getchar simply uses the standard input to read a character. 

We can implement it as follows:  

```c
#define getchar() getc(stdin)
```

**char[] fgets(char line [], int maxlen,FILE∗ fp)**

- reads a single line (upto maxlen characters) from the input stream (including linebreak).
- returns a pointer to the character array that stores the line (read-only)
- return NULL if end of stream.

### File output

**int putc(int c,FILE∗ fp)**

- writes a single character c to the output stream.
- returns the character written or EOF on error.

Note: putchar simply uses the standard output to write a character. We can implement it as follows:

```c
#define putchar(c) putc(c,stdout)
```

**int fputs(char line [], FILE∗ fp)**

- writes a single line to the output stream.
- returns zero on success, EOF otherwise.

**int fscanf(FILE∗ fp,char format[],arg1,arg2)**

- similar to scanf,sscanf
- reads items from input stream fp.

## Command line input

- In addition to taking input from standard input and files, you can also pass input while invoking the program.
- Command line parameters are very common in *nix environment.
- So far, we have used int main() as to invoke the main function. However, main function can take arguments  that are populated when the program is invoked.

**int main(int argc,char∗ argv[])**

- **argc**: count of arguments.
- **argv[]**: an array of pointers to each of the arguments

Note: the arguments include the name of the program as well.

