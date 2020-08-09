CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

level1.o: level1.cpp level1.hpp
	$(CC) -shared $(CFLAGS) $(THREAD) level1.cpp $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml