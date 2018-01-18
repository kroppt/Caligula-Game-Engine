#Greg is ergi
CXXFLAGS=-I/usr/include/SDL2 -I/usr/include/libdrm -O4 -std=gnu++17 -Wall -Wextra -D_REENTRANT -Iaudio
LDLIBS=-ldrm -lSDL2 -lGL -lm 
LDFLAGS=-O4 -flto

OBJECTS=audio/AudioInterface.o main.o
.PHONY: git

caligula: $(OBJECTS)
	$(CXX) -o caligula $(OBJECTS) $(LDFLAGS) $(LDLIBS)


git:
	git submodule init
	git submodule update

clean:
	rm $(OBJECTS)