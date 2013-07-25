#ifndef _binarybuddies_h_
#define _binarybuddies_h_

int start_memory(int size);
void *get_memory(int size);
void release_memory(void *p);
void end_memory(void);

#endif /* _binarybuddies_h_ */