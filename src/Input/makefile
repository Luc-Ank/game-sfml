CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: input.o

input.o: input.cpp input.hpp
	$(CC) -shared $(CFLAGS) $(THREAD) input.cpp $(SFML)

clean:
	\rm *.o 