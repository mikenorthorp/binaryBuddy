#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//global vars
int totalMemory; //this is the total memory that malloc gets in start_memory minus the struct memory

int freeMemory;

int usedMemory;

// Depth to check how many levels have been created
int depth = 0;

int buddy = 1;

int side = 1;

//base pointer returned by malloc
void *mallocPointer;

// Header struct containing memory size, if it is used, pointer to the memory address of header
// and the a
typedef struct
{
    // Total header size = 4bytes after padding
    // Check if is used - 2bytes
    short isUsed;
    // Storage of right or left side (1 = left 2 = right) - 2byte
    short side;
} buddyNode;

typedef struct
{
    int mem1;
} testStruct;

// Initializes a single malloc call to a passed in size in bytes, and stores a global
// pointer to the root header containing the root block.
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

// This mallocs
void *get_memory( int size )
{
    // Set up header to be created
    int partitionSizeCurrent;
    int partitionSizeLowest;
    int tempCount = 0;
    int i = freeMemory;
    // Calculate the partition size to search block for first level
    partitionSizeCurrent = 1;
    partitionSizeLowest = 1;

    i = i - sizeof(buddyNode);

    // Find how many levels need to go unless it fits in top block
    while (size < (i / 4))
    {
        i = freeMemory;

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

        i = ((i - ((partitionSizeCurrent) * sizeof(buddyNode))) / (partitionSizeCurrent));
    }
    int currentFreeMem = i;

    // Check blocks for current depth until we find one without a header or a unused header
    void *currentLevelPointer;
    void *tempPointer;

    int passAll = 0;
    int blockCounter;

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

        printf("Checking %d partition", blockCounter + 1);
        printf("This is the current free size: %d\n", currentFreeMem);
        int blockSize = (blockCounter * (currentFreeMem + sizeof(buddyNode)));
        printf("Size of block is : %d\n", blockSize);
        tempPointer = mallocPointer + blockSize;

        if ( ((buddyNode *)tempPointer)->isUsed == 0 || ((buddyNode *)tempPointer)->isUsed == NULL)
        {
            void *buddyCheck;
            // Additional check to see where buddy is
            if (((buddyNode *)tempPointer)->isUsed == 0)
            {
            	printf("Is used is 0 and not null or 1\n");
                // Check if left or right
                // Left
                if (side == 1)
                {
                    buddyCheck = tempPointer + (currentFreeMem + sizeof(buddyNode));
                    if (((buddyNode *)buddyCheck)->isUsed == 0 || ((buddyNode *)buddyCheck)->isUsed == 1)
                    {
                    	printf("Pass all is 1\n");
                        passAll = 1;
                    }
                    else
                    {
                    	printf("Pass all is 0\n");
                        passAll = 0;
                    }
                }
                // Right
                else if (side == 2)
                {
                    buddyCheck = tempPointer - (currentFreeMem + sizeof(buddyNode));
                    if (((buddyNode *)buddyCheck)->isUsed == 0 || ((buddyNode *)buddyCheck)->isUsed == 1)
                    {
                    	printf("Pass all is 1\n");
                        passAll = 1;
                    }
                    else
                    {
                    	printf("Pass all is 0\n");
                        passAll = 0;
                    }
                }
            } else {
            	printf("Pass all is 1\n");
            	passAll = 1;
            }

            printf("this is the passAll: %d\n", passAll);
            currentLevelPointer = tempPointer;
            break;
        }
    }

    printf("%p\n", currentLevelPointer);

    // Check smallest depth blocks for lower memory taking up this single block and all levels up to
    // current depth

    // If passes all checks make a buddyNode at the address found and return it
    if (passAll == 1)
    {
        // Set up base buddyNode struct pointer to the returned malloc address
        buddyNode *node = currentLevelPointer;
        // Set used
        node->isUsed = 1;
        // Set if side is left or right (1 = left 2 = right)
        node->side = side;

        printf("Created node at %p\n", currentLevelPointer);

        void *newPointer;
        int newBlockSize = sizeof(buddyNode) + currentFreeMem;

        if (side == 1)
        {
            printf("Is left side node\n");
            newPointer = (currentLevelPointer + newBlockSize);
            side = 2;
        }
        else if (side == 2)
        {
            printf("Is right side node\n");
            newPointer = (currentLevelPointer - newBlockSize);
            side = 1;
        }
        else
        {
            printf("You broke the sides\n");
        }

        buddyNode *nodeBuddy = newPointer;
        // Set not used
        if ( nodeBuddy->isUsed == 1)
        {
            printf("This buddy is used\n");
        }
        else
        {
            printf("This buddy is not used\n");
            // Initialize
            nodeBuddy->isUsed = 0;
        }

        // Set if side is left or right (1 = left 2 = right)
        nodeBuddy->side = side;

        printf("Created buddy node at %p\n", nodeBuddy);

        // Return the current level pointer
        return (void *)currentLevelPointer;
    }
    else
    {
        printf("Cannot allocate memory");
        return NULL;
    }
}


// This releases the memory from the pointer
void release_memory( void *p ) {
	// Just set the pointer to not be used, making it unallocated now
	((buddyNode *)p)->isUsed == 0;
	printf("Released memory at %p\n", p);
}

void end_memory(void) {
	printf("Test");
}

// Main testing
int main( int argc, char **argv )
{
    start_memory(2048);

    printf("Print out malloc pointer for initial check\n");
    printf("%p\n", mallocPointer);

    // Attempt to get memory
    get_memory(2);
    int testSize = sizeof(testStruct);
    printf("Size is %d\n", testSize);
    testStruct *test1 = get_memory(testSize);
    printf("%p\n", (void *)test1);

    printf("Size is %d\n", testSize);
    testStruct *test2 = get_memory(testSize);
    printf("%p\n", (void *)test2);

    printf("Size is %d\n", testSize);
    testStruct *test3 = get_memory(testSize);
    printf("%p\n", (void *)test3);

    // Test release memory
    release_memory(test3);

    // Test end_memory
    end_memory();


    // Exit main
    return 1;
}
