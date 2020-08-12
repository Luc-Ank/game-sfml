CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: levelWindow.o tileWindow.o

Window.o: Window.cpp
	$(CC) -shared $(SFML) $(CFLAGS) $(THREAD) Window.cpp


clean:
	\rm *.o 

