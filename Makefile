CXXFLAGS=-I/usr/include/SDL2 -I/usr/include/libdrm -Iinclude -O4 -std=gnu++17 -Wall -Wextra -D_REENTRANT -Iaudio
LDLIBS=-ldrm -lSDL2 -lGL -lm 
LDFLAGS=-O4 -flto

OBJECTS=main.o audio/AudioInterface.o
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