FLAGS=-I/usr/include/freetype2 -I/usr/include/SDL2 -I/usr/include/libdrm -Iinclude -O4  -Wall -Wextra -D_REENTRANT -Iaudio -g -I.
CXXFLAGS=$(FLAGS) -std=gnu++17
CFLAGS=$(FLAGS) -std=gnu11
LDLIBS=-lcairo -lharfbuzz -lfreetype -ldrm -lSDL2 -lSDL2_image -lGL -lm -ldl -lpng -lconfig++
LDFLAGS=-O4 -flto -g

OBJECTS=src/main.o src/window.o src/world.o src/resource_manager.o src/fps_counter.o src/model.o src/camera.o src/entity.o src/shader_program.o audio/AudioInterface.o src/glad.o src/texture.o src/textrender.o src/linalg.o src/io.o src/random.o src/config.o
.PHONY: git clean push pull commit
all: caligula
caligula: $(OBJECTS)
	$(CXX) -o caligula $(OBJECTS) $(LDFLAGS) $(LDLIBS)
tools: obj_to_ply.o
	gcc
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
	rm -f $(OBJECTS)
