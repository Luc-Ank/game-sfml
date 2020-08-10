CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: game-sfml

debug: all

input.o: input.cpp input.hpp
	$(CC) -shared $(CFLAGS) $(THREAD) input.cpp $(SFML)

clean:
	\rm *.o game-sfml

run: all
run:
	./game-sfml