FLAGS=-I/usr/include/SDL2 -I/usr/include/libdrm -Iinclude -O4  -Wall -Wextra -D_REENTRANT -Iaudio -g
CXXFLAGS=$(FLAGS) -std=gnu++17
CFLAGS=$(FLAGS) -std=gnu11
LDLIBS=-ldrm -lSDL2 -lGL -lm -ldl
LDFLAGS=-O4 -flto -g

OBJECTS=main.o audio/AudioInterface.o src/glad.o
.PHONY: git clean push pull commit
all: caligula
caligula: $(OBJECTS)
	$(CXX) -o caligula $(OBJECTS) $(LDFLAGS) $(LDLIBS)


git:
	git submodule init
	git submodule update
commit:
	git commit -a
push:
	git push origin master
pull:
	git pull origin master
clean:
	rm $(OBJECTS)