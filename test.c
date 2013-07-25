#include <stdio.h>
#include <stdlib.h>
#include "binarybuddies.h"

// Test struct of 4 bytes for testing
typedef struct
{
    int mem1;
} testStruct;

// Main testing
int main( int argc, char **argv )
{
    start_memory(2048);

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