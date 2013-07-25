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
    printf("Running basic tests, you can run your own these are just examples..\n");
    printf("Initializing memory to 2048bytes\n");
    start_memory(2048);

    // Attempt to get memory
    printf("The following test the get memory function\n");
    printf("The address for 2bytes of memory is %p\n", get_memory(2));
    int testSize = sizeof(testStruct);
    printf("Size is %d", testSize);
    testStruct *test1 = get_memory(testSize);
    printf(" and address is %p\n", (void *)test1);

    printf("Size is %d", testSize);
    testStruct *test2 = get_memory(testSize);
    printf(" and address is %p\n", (void *)test2);

    printf("Size is %d", testSize);
    testStruct *test3 = get_memory(testSize);
    printf(" and address is %p\n", (void *)test3);

    // Test release memory on third struct
    release_memory(test3);

    // Test end_memory on remaining structs
    printf("Testing release memory on remaining stuff, should display leaks and free everything\n");
    end_memory();


    printf("End of testing\n");
    // Exit main
    return 1;
}