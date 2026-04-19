#CC = g++
CC = gcc
OBJS = hello_world.o circ_buf.o linked_list.c

all: $(OBJS)
	$(CC) -o hello_world $(OBJS)
#	g++ -o hello_world hello_world.c

run:
	./hello_world

clean:
	rm -rf *.o
