all: all.o
	g++ -o simp main.o shader.o shape.o camera.o glad.o -ldl -lglfw && rm *.o

all.o: src/main.cpp src/shader.cpp src/shape.cpp src/camera.cpp src/glad.c
	g++ -c src/main.cpp src/shader.cpp src/shape.cpp src/camera.cpp src/glad.c
