CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

game-sfml: main.o 
	$(CC) $(THREAD) main.o -o game-sfml $(SFML)

main.o: main.cpp
	$(CC) $(THREAD) main.cpp $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml