/* binarybuddies.c
   June 29th, 2013
   Michael Northorp & Robert MacIsaac - CSCI 3120 - Assignment 5
   This is a memory managment library using the binary buddy memory managment
   system. It has implemenmtations for initializing memory with a single malloc
   call based on user arguments. Then it has get_memory which takes in a size to
   allocate enough memory for that side, as well as a free memory which takes in
   a pointer to a memory location, and a end_memory that cleans everything up and
   displays leaks. */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Global variables */

// This is the total memory that malloc gets in start_memory minus the struct memory
int totalMemory;

// This is the amount of free memory avaialble
int freeMemory;

// Depth to check how many levels have been created
int depth = 0;
// Lowest possible block size based on the lowest depth
int lowestBlockSize = 0;

// This is the side of the buddy (1 = left, 2 = right)
int side = 1;

// Initial pointer returned by malloc
void *mallocPointer;

// Header contains if it is used and the side the node is on
typedef struct
{
    // Total header size = 4bytes after padding
    // Check if is used - 2bytes
    short isUsed;
    // Storage of right or left side (1 = left 2 = right) - 2byte
    short side;
} buddyNode;



// Initializes a single malloc call to a passed in size in bytes, and stores a global pointer
int start_memory(int size)
{
    // Try to allocate the size taken in by the start memory function
    if ((mallocPointer = malloc(size)))
    {
        // Set size to the global variable total memory
        totalMemory = size;
        // Set free memory to total minus used
        freeMemory = totalMemory;

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



// This gets a size as an argument in bytes and allocates memory to the user in our
// binary buddy system and returns an address to the allocated memory as a pointer
// to the user.
void *get_memory( int size )
{
    // Set up variables needed for number of segements
    int partitionSizeCurrent;
    int partitionSizeLowest;

    // Other variables for a temp depth counter and storing free memory
    int tempCount = 0;
    int i = freeMemory;


    // Calculate the partition size to search block for first level
    partitionSizeCurrent = 1;
    partitionSizeLowest = 1;

    // Subtract header from initial block size and then do a while loop to check
    // If memory will fit
    i = i - sizeof(buddyNode);

    // Find how many levels need to go unless it fits in top block
    while (size < (i / 4))
    {
        // Set i to freeMemory initial size again
        i = freeMemory;

        // Increase the depth
        tempCount++;

        // Increase depth if new call goes lower
        if (tempCount > depth)
        {
            depth = tempCount;
        }

        // Calculate the partition size to search block for current tempCount depth
        partitionSizeCurrent = (int)pow(2.0, ((double)tempCount));
        // Calculate the partition size to search block for lowest possible depth
        partitionSizeLowest = (int)pow(2.0, ((double)depth));

        // Get the new amount of free memory per block based on the current depth
        i = ((i - ((partitionSizeCurrent) * sizeof(buddyNode))) / (partitionSizeCurrent));

        // Assign the lowest block size to be used later when freeing memory.
        lowestBlockSize = (i + sizeof(buddyNode));
    }

    // Save the current free memory after breaking out of the while loop
    int currentFreeMem = i;

    // Check blocks for current depth until we find one without a header or a unused header
    // Pointers for the address to put the new block and a temp pointer for other checks
    void *currentLevelPointer;
    void *tempPointer;

    // Checks if we can allocate memory if all checks are passed
    int passAll = 0;

    // Counter for loop
    int blockCounter;

    // Loops through all possible blocks in the current parition size until it finds a free space
    for (blockCounter = 0; blockCounter < partitionSizeCurrent; blockCounter++)
    {
        // See if its on left or right
        if (blockCounter % 2 == 0)
        {
            side = 1;
        }
        else
        {
            side = 2;
        }

        // Set the block size
        int blockSize = (blockCounter * (currentFreeMem + sizeof(buddyNode)));

        // Set a temp pointer to check if block has a buddy
        tempPointer = mallocPointer + blockSize;

        // See if block is unsed or not initialized
        if (((buddyNode *)tempPointer)->isUsed == 0)
        {
            void *buddyCheck;
            // Additional check to see where buddy is
            if (((buddyNode *)tempPointer)->isUsed == 0)
            {
                // Check if left or right
                // Left
                if (side == 1)
                {
                    buddyCheck = tempPointer + (currentFreeMem + sizeof(buddyNode));
                    if (((buddyNode *)buddyCheck)->isUsed == 0 || ((buddyNode *)buddyCheck)->isUsed == 1)
                    {
                        passAll = 1;
                    }
                    else
                    {
                        passAll = 0;
                    }
                }
                // Right
                else if (side == 2)
                {
                    buddyCheck = tempPointer - (currentFreeMem + sizeof(buddyNode));
                    if (((buddyNode *)buddyCheck)->isUsed == 0 || ((buddyNode *)buddyCheck)->isUsed == 1)
                    {
                        passAll = 1;
                    }
                    else
                    {
                        passAll = 0;
                    }
                }
            }
            else
            {
                passAll = 1;
            }

            // Set currentLevelPointer to the tempPointer and break out
            currentLevelPointer = tempPointer;
            break;
        }
    }

    // If passes all checks make a buddyNode at the address found and return it and create its buddy to the left
    // or right
    if (passAll == 1)
    {
        // Set up base buddyNode struct pointer to the returned malloc address
        buddyNode *node = currentLevelPointer;
        // Set used
        node->isUsed = 1;
        // Set if side is left or right (1 = left 2 = right)
        node->side = side;

        void *newPointer;
        int newBlockSize = sizeof(buddyNode) + currentFreeMem;

        // Figure out where the buddy should go, on left or right of current node
        if (side == 1)
        {
            newPointer = (currentLevelPointer + newBlockSize);
            side = 2;
        }
        else if (side == 2)
        {
            newPointer = (currentLevelPointer - newBlockSize);
            side = 1;
        }
        else
        {
            printf("You broke the sides\n");
        }

        // Set nodeBuddy to the newPointer we just found
        buddyNode *nodeBuddy = newPointer;

        // Set not used
        if ( nodeBuddy->isUsed == 1)
        {
            // Buddy is used so dont set to unused
        }
        else
        {
            // Initialize too 0
            nodeBuddy->isUsed = 0;
        }

        // Set if side is left or right (1 = left 2 = right)
        nodeBuddy->side = side;

        // Return the current level pointer (The original requested memory address)
        return (void *)currentLevelPointer;
    }
    // Cannot allocate memory if it gets here
    else
    {
        printf("Cannot allocate memory");
        return NULL;
    }
}



// This releases the memory from the pointer
void release_memory( void *p )
{
    // Just set the pointer to not be used, making it unallocated now
    ((buddyNode *)p)->isUsed = 0;
    printf("Released memory at %p\n", p);
}




// This goes through every possible header that could of been created and shows if
// it is still being used, in which cases it prints out a memory leak and then releases
// it by setting it to unused. It then frees the initial mallocPointer created at the
// start to clean everything up.
void end_memory(void)
{
    // Loop through all the possible headers at lowest possible depth
    // Calculate the partition size to search block for lowest possible depth
    int partitionSizeLowest = (int)pow(2.0, ((double)depth));
    int blockSize = lowestBlockSize;
    void *pointer;

    int i;

    // Loop through all possible headers
    for (i = 0; i < partitionSizeLowest; i++)
    {
        pointer = (mallocPointer + (i * (blockSize)));
        if (((buddyNode *)pointer)->isUsed == 1)
        {
            printf("You have a leak at block %p\n", pointer);
            printf("Releasing memory at block %p\n", pointer);

            //Release it
            ((buddyNode *)pointer)->isUsed = 0;
        }
    }

    // Free initial malloc call
    free(mallocPointer);
}