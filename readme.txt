README
======

README and code base best viewed on [Github](https://github.com/mikenorthorp/binaryBuddy)


This is an assignment for my Operating Systems class CSCI 3120 worked on with my partner Rob MacIsaac

It is a memory managment library using the binary buddy memory managment
system.

It has implemenmtations for initializing memory with a single malloc
call based on user arguments. Then it has get\_memory which takes in a size to
allocate enough memory for that side, as well as a free memory which takes in
a pointer to a memory location, and a end\_memory that cleans everything up and
displays leaks.

Non implemented functions are grow_memory and pre\_grow memory which add extra memory
to the end of the parition or relocates if it does not have enough room in the current block, and
pre\_grow adds to the front of the parition.


Requirements
------------

This program requires `gcc` and `make` to compile if you want to run our example

Since this is a library you can include it by dropping in the `binarybuddies.c` and
`binarybuddies.h` file, and including it by using `#include "binarybuddies.h"`

This program is made to run on the bluenose.cs.dal.ca servers but should work
on most linux distros.

Installation
------------

1. Copy files into working directory.
2. run `make` command in terminal
3. run `./binarybuddies`
4. Or include it as seen in the requirments sections and allocate memory yourself using the functions

Method Descriptions
------------------

#### Memory Functions ####

int start_memory(int size)

	- This initializes the total memory at the size passed in by the user. The program will only be allowed to access “size” bytes of memory. A program will only call start memory function once (at the start of the program).

void *get_memory( int size )

	- This gets a size as an argument in bytes and allocates memory to the user in our
	  binary buddy system and returns an address to the allocated memory as a pointer
	  to the user.

void release_memory( void *p )

	- Releases memory partition referenced by pointer “p” back to free space.

void end_memory(void)

	- This goes through every possible header that could of been created and shows if
	  it is still being used, in which cases it prints out a memory leak and then releases
	  it by setting it to unused. It then frees the initial mallocPointer created at the
	  start to clean everything up.


Test Cases
----------

See the test file that is run as an example and check out blackWhiteTests.txt for black box and white box test cases







