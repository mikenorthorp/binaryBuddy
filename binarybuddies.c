#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//global vars
int totalMemory; //this is the total memory that malloc gets in start_memory minus the struct memory

int freeMemory;

int usedMemory;

//base pointer returned by malloc
void *mallocPointer;

// Base pointer to our top level header
void *basePointer;

// Header struct containing memory size, if it is used, pointer to the memory address of header
// and the a
typedef struct
{
    // Total header size = 16bytes after padding
    // Short for size of memory up to 4294967296 bytes - 4bytes
    int memSize;
    // Flag for if memory is used or not - 2byte
    short isUsed;
    // Storage of buddy number - 2byte
    short buddy;
    // Pointer to the memory address of this node - 2bytes
    void *memPointer;
} buddyNode;

// Initializes a single malloc call to a passed in size in bytes, and stores a global
// pointer to the root header containing the root block.
int start_memory(int size)
{
    // Try to allocate the size taken in by the start memory function
    if ((mallocPointer = malloc(size)))
    {
        // Set size to the global variable total memory
        totalMemory = size;

        // Set up base buddyNode struct pointer to the returned malloc address
        buddyNode *root = (buddyNode *)mallocPointer;

        // Set initial free space (total minus header)
        root->memSize = (totalMemory - sizeof(buddyNode));
        // Set not used
        root->isUsed = 0;
        // Set buddy number
        root->buddy = 0;
        // Set the address to the very start of root block
        root->memPointer = mallocPointer;

        // Set global base pointer to the buddyNode root
        basePointer = (void *)root;

        // Return 1 on sucess
        return 1;
    }
    // Return 0 on fail
    else
    {
        printf("Could not allocate memory\n");
        return 0;
    }
}

// This mallocs
void *get_memory( int size )
{
	//declare buddy node to be created
	buddyNode node;
}

int main( int argc, char **argv )
{
    printf("Test\n");
    start_memory(256);
    printf("End start mem\n");
    printf("Print out malloc pointer for initial check\n");
    printf("%p\n", mallocPointer);
    printf("Print root address, isUsed, memsize and buddy\n");
    printf("%p\n", ((buddyNode *)basePointer)->memPointer);
    printf("%d\n", ((buddyNode *)basePointer)->isUsed);
    printf("%d\n", ((buddyNode *)basePointer)->memSize);
    printf("%d\n", ((buddyNode *)basePointer)->buddy);

    return 1;
}
