#include <stdio.h>
#include <stdlib.h>

//global vars
int totalMemory; //this is the total memory that malloc gets in start_memory minus the struct memory

int freeMemory;

int usedMemory;

//base pointer returned by malloc
void *basePointer;
//pointer to array
void *arrayPointer;


typedef struct
{
    //integer for size of memory in node
    int memSize;
    //integer to act aqs a flag to designate whether or not the memory is used. 1 for used, 0 for free
    char isUsed;
    //char to designate which node is the buddy of this one; i.e: 1 and 1 are buddies, 2 and 2 are buddies etc...
    char buddy;
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
        //while loop to get hte nu,mber of possible buddies
        size = size - (sizeOf(buddyNode));
        usedMemory += (sizeOf(buddyNode));
        while (size / 2 != 4)
        {
            numberOfBuddies++;
            size = size - (sizeOf(buddyNode) * 2);
            size = size / 2;
            usedMemory += (sizeOf(buddyNode) * 2);
        }

        freeMemory = totalMemory - usedMemory;

        //include a data structure here
        void buddies[numberOfBuddies * 2 + 1];

        //base partition
        buddyNode base = basePointer;

        base.memSize = freeMemory;
        base.isUsed = 0;
        base.buddy = 0;

        buddies[0] = (void*)basePointer;

        //set up all the structs were going to use and assign them memory from the malloc call
        int i = 0
                for (i = 0; i <= numberOfBuddies; i++)
        {
            buddies[i * 2] = buddyNode
                             buddies[i * 2 + 1] = buddyNode
        }
        //set global pointer to point to array
        arrayPointer = buddies;





        return 1;
    }

    else
        reutrn 0;
}
