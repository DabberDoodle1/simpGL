all: all.o
	g++ -o simp main.o shaders.o glad.o -ldl -lglfw && rm *.o && ./simp

all.o: src/main.cpp src/shaders.cpp src/glad.c
	g++ -c src/main.cpp src/shaders.cpp src/glad.c
