
#Thisnext linedefines arguments that are passed to all compilation steps

CCFLAGS = -g -Wall

binarybuddies: binarybuddies.o
	gcc $(CCFLAGS) -o binarybuddies binarybuddies.o -lm

binarybuddies.o: binarybuddies.c
	gcc $(CCFLAGS) -c binarybuddies.c -lm

clean:
	-rm binarybuddies binarybuddies.o
