CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: collision.o

collision.o: collision.cpp collision.hpp
	$(CC) -shared $(CFLAGS) $(THREAD) collision.cpp $(SFML)

clean:
	\rm *.o 
