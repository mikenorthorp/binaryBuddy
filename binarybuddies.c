#include <stdio.h>
#include <stdlib.h>
//global vars
//http://simplestcodings.blogspot.ca/2012/10/abstract-binary-search-tree.html - binary tree we could use
BinaryTree tree;
int memoryAvaliable;

//where the only malloc call is permitted
int start_memory(int size)
{
	//if structs are used to keep track of mem blocks this malloc will have to account for them as well
	if(malloc(size))
	{
		//find a way to keep track of mem blocks given to us by malloc, a struct maybe?

		memoryAvaliable = size;
		return 1;
	}

	else
		reutrn 0;
}

void *get_memory(int size)
{
	Node currentNodeInBinaryTree = tree.root();

	if(memoryAvaliable >= size)
	{
		while(currentNodeInBinaryTree.size() - size > currentNodeInBinaryTree.size()/2)
		{
			Tree.add(currentNodeInBinaryTree/2);
			currentNodeInBinaryTree = tree.next();
		}

		memoryAvaliable -= size;

		return (void*)currentNodeInBinaryTree;
	}
	else
		return NULL;

}

void release_memory(void *p)
{
	//mark the nodes pointed to by tyhe pointer as having a value of 0 (empty)
	//probably going to need to cast it to 'Node'
	Node currentNodeInBinaryTree = p;
	//add the total memory freed back to the avaliable memory
	memoryAvaliable += currentNodeInBinaryTree;

	currentNodeInBinaryTree = 0;

	//check to see if we can reclaim the buddies by checking the parent node
	currentNodeInBinaryTree = currentNodeInBinaryTree.parent();

	if(currentNodeInBinaryTree.leftNode() == 0 && currentNodeInBinaryTree.rightNode()==0)
	{
		currentNodeInBinaryTree.deleteLeftNode();
		currentNodeInBinaryTree.deleteRightNode();
	}
}

void *grow_memory(int size, void *p)
{
	//find out what mem block p points to
	//memory in mem block = memory in mem block + size
}



//tear down method
void end_memory()
{
	
	//reclaim all mem blocks were keeping track of
	//break down binary tree
	//free the memory we claimed
	free(sizeOf(mem blocks));

}