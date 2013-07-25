#ifndef _binarybuddies_h_
#define _binarybuddies_h_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int start_memory(int size);
void *get_memory(int size);
void release_memory(void *p);
void end_memory(void);

#endif /* _binarybuddies_h_ */