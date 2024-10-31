all: all.o
	g++ -o simp main.o shader.o shape.o glad.o -ldl -lglfw && rm *.o && ./simp

all.o: src/main.cpp src/shader.cpp src/shape.cpp src/glad.c
	g++ -c src/main.cpp src/shader.cpp src/shape.cpp src/glad.c
