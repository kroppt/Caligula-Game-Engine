CFLAGS=-std=gnu11 -g -O4 -Wall -Wextra -I.
LDFLAGS=-O4 -flto -g
OBJECTS=obj_to_ply.o ply_io.o 

.PHONY=all clean

all: $(OBJECTS) obj_to_ply plato_ply

clean:
	$(RM) -f $(OBJECTS) obj_to_ply plato_ply

obj_to_ply: obj_to_ply.o ply_io.o

plato_ply: plato_ply.o ply_io.o
