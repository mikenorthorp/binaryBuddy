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

//base pointer returned by malloc
void *mallocPointer;

// Header struct containing memory size, if it is used, pointer to the memory address of header
// and the a
typedef struct
{
    // Total header size = 16bytes after padding
    // Short for size of memory up to 4294967296 bytes - 4bytes
    int memSize;
    // Check if is used - 2bytes
    short isUsed;
    // Storage of buddy number - 2byte
    short buddy;
    // Pointer to the memory address of this node - > 2 bytes
    void *memPointer;
} buddyNode;

typedef struct
{
    long mem33;
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
    // Find how many levels need to go
    while (size <= i / 2)
    {
        printf("free memory is %d\n", i);
        tempCount++;
        printf("Depth is %d\n", depth);
        // Increase depth if new call goes lower
        if (tempCount > depth)
        {
            depth = tempCount;
        }

        i = ((i - ((tempCount + 1) * sizeof(buddyNode))) / 2);
        // Calculate the partition size to search block for current tempCount depth
        partitionSizeCurrent = (int)pow(2.0, ((double)tempCount));
        // Calculate the partition size to search block for lowest possible depth
        partitionSizeLowest = (int)pow(2.0, ((double)depth));
    }

    // Testing depth parition sizes
    printf("Printing current depth partition size:");
    printf(" %d\n", partitionSizeCurrent);
    printf("Printing lowest depth partition size:");
    printf(" %d\n", partitionSizeLowest);

    // Check blocks for current depth until we find one without a header or a unused header
    void *currentLevelPointer;
    void *tempPointer;
    int passAll;
    for (i = 0; i < partitionSizeCurrent; i++)
    {
        printf("Checking %d partition", i + 1);
        printf("This is the parition size: %d\n", totalMemory / partitionSizeCurrent);
        tempPointer = mallocPointer + (i * (totalMemory / partitionSizeCurrent));

        if ( ((buddyNode *)tempPointer)->isUsed == 0 || ((buddyNode *)tempPointer)->isUsed == NULL)
        {
            printf("Found null\n");
            currentLevelPointer = tempPointer;
            break;
        }
    }

    printf("%p\n", currentLevelPointer);

    // Check smallest depth blocks for lower memory taking up this single block and all levels up to
    // current depth

    // If passes all checks make a buddyNode at the address found and return it
    passAll = 1;
    if (passAll == 1)
    {
        // Set up base buddyNode struct pointer to the returned malloc address
        buddyNode *node = currentLevelPointer;
        // Set initial free space (total minus header)
        node->memSize = (totalMemory / partitionSizeCurrent);
        // Set not used
        node->isUsed = 1;
        // Set buddy number
        node->buddy = buddy;
        buddy++;
        // Set the address to the currentLevelPointer
        node->memPointer = currentLevelPointer;

        printf("Created node at %p\n", ((buddyNode *)node)->memPointer);
        return (void *)currentLevelPointer;
    }
    else
    {
        printf("Cannot allocate memory");
        return NULL;
    }
}

// Main testing
int main( int argc, char **argv )
{
    printf("Test\n");
    start_memory(32);
    printf("End start mem\n");
    printf("Print out malloc pointer for initial check\n");
    printf("%p\n", mallocPointer);

    // Attempt to get memory
    printf("Get the memory of testStruct\n");
    int testSize = sizeof(testStruct);
    printf("Size is %d\n", testSize);
    testStruct *test1 = get_memory(testSize);
    printf("%p\n", (void *)test1);

    printf("Size is %d\n", testSize);
    testStruct *test2 = get_memory(testSize);
    printf("%p\n", (void *)test2);


    return 1;
}
