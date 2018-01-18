#Greg is ergi
CXXFLAGS=-I/usr/include/SDL2 -I/usr/include/libdrm -O4 -std=gnu++17 -Wall -Wextra -Werror -D_REENTRANT -Iaudio
LDLIBS=-ldrm -lsdl2 -lGL -lm 
LDFLAGS=-O4 -flto

OBJECTS=main.o audio/AudioInterface.o
.PHONY: git

caligula: $(OBJECTS)
	$(CXX) -o caligula $(OBJECTS) $(LDFLAGS) $(LDLIBS)


git:
	git submodule init
	git submodule update