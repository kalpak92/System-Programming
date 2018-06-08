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

