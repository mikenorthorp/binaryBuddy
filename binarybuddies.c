#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//global vars
int totalMemory; //this is the total memory that malloc gets in start_memory minus the struct memory

int freeMemory;

int usedMemory;

//base pointer returned by malloc
void *basePointer;


typedef struct
{
    //integer for size of memory in node
    short memSize;
    //integer to act aqs a flag to designate whether or not the memory is used. 1 for used, 0 for free
    char isUsed;
    // Pointer to the memory address of this node
    void *memPointer;
} buddyNode;

int start_memory(int size)
{
    //if structs are used to keep track of mem blocks this malloc will have to account for them as well
    if (basePointer = malloc(size))
    {
        //get size into a global variable
        totalMemory = size;
        //tracks the number of possible buddies
        int numberOfBuddies = 0;
        //while loop to get the number of possible buddies
        size = size - (sizeof(buddyNode));
        usedMemory += (sizeof(buddyNode));
        while (size / 2 != 4)
        {
            numberOfBuddies++;
            size = size - (sizeof(buddyNode) * 2);
            size = size / 2;
            usedMemory += (sizeof(buddyNode) * 2);
        }

        freeMemory = totalMemory - usedMemory;

        //include a data structure here
        void *buddies[numberOfBuddies * 2 + 1];

        //base partition
        buddyNode *base = basePointer;

        base.memSize = freeMemory;
        base.isUsed = 0;
        base->memPointer = basePointer;

        buddies[0] = (void *)basePointer;

        //set up all the structs were going to use and assign them memory from the malloc call
        int i;
        int j;
        double count;
        int k = 1;
        for (i = 1; i < numberOfBuddies; i++)
        {
            // Figure out how many sets of buddys to make
            count = pow(2.0, (double)i) / 2;


            for (j = 0; j < count; j++)
            {
                int blockSize = freeMemory / (count*2);
                int buddySize = sizeof(buddyNode);

                // Set up first buddy
                buddyNode node1 = basePointer + ((j*2) * (blockSize + buddySize));
                node1.memSize = blockSize;
                node1.isUsed = 0;
                node1->memPointer = basePointer + ((j*2) * (blockSize + buddySize));

                // Set up second buddy
                buddyNode node2 = basePointer + (((j*2)+1) * (blockSize + buddySize));
                node2.memSize = blockSize;
                node2.isUsed = 0;
                node2->memPointer = basePointer + (((j*2)+1) * (blockSize + buddySize));

                // Put buddy nodes into array with their header and mempointers and size
				int buddy1Pos = 2*k-1;
				int buddy2Pos = 2*k;
                buddies[buddy1Pos] = (void *)node1;
                buddies[buddy2Pos] = (void *)node2;
                k++;
            }
        }
        //set global pointer to point to array
        arrayPointer = buddies;


        return 1;
    }
    else
    {
        return 0;
    }
}
