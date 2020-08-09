CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

game-sfml: test.o Map/map.o Level/level1.o
	$(CC) $(THREAD) test.o Map/map.o Level/level1.o -o game-sfml $(SFML)

test.o: test.cpp
	$(CC) $(CFLAGS) $(THREAD) test.cpp $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml