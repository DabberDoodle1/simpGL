all: all.o
	g++ -Wall -o simp main.o shader.o shape.o camera.o game.o glad.o -ldl -lglfw && rm *.o

all.o: src/main.cpp src/shader.cpp src/shape.cpp src/camera.cpp src/game.cpp src/glad.c
	g++ -c src/main.cpp src/shader.cpp src/shape.cpp src/camera.cpp src/game.cpp src/glad.c
