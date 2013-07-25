
#Thisnext linedefines arguments that are passed to all compilation steps

CCFLAGS = -g -Wall

binarybuddies: test.o binarybuddies.o binarybuddies.h
	gcc $(CCFLAGS) -o binarybuddies test.c binarybuddies.o -lm

binarybuddies.o: binarybuddies.c binarybuddies.h
	gcc $(CCFLAGS) -c binarybuddies.c -lm

clean:
	-rm binarybuddies binarybuddies.o test.o
