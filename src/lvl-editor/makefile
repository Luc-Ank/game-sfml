CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: levelWindow.o Window.o

Window.o: Window.cpp Window.h
	$(CC) -shared $(SFML) $(CFLAGS) $(THREAD) Window.cpp

levelWindow.o: Window.cpp Window.h
	$(CC) -shared $(SFML) $(CFLAGS) $(THREAD) Window.cpp


clean:
	\rm *.o 

