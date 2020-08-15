CC = clang++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: levelWindow.o Window.o

debug: DEBUG += -g -fsanitize=address
debug: all

Window.o: Window.cpp Window.h
	$(CC) -shared $(SFML) $(DEBUG) $(CFLAGS) Window.cpp

levelWindow.o: Window.cpp Window.h
	$(CC) -shared $(SFML) $(CFLAGS) Window.cpp


clean:
	\rm *.o 

