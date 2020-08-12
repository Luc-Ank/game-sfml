CC = g++
CFLAGS = -c
DEBUG = -Wall -Werror -Wextra
THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: levelWindow.o tileWindow.o

levelWindow.o: levelWindow.cpp
	$(CC) -shared $(SFML) $(CFLAGS) $(THREAD) levelWindow.cpp

tileWindow.o: tileWindow.cpp
	$(CC) -shared $(SFML) $(CFLAGS) $(THREAD) tileWindow.cpp

# map.o: map.cpp map.hpp map1.txt
# 	$(CC) -shared $(CFLAGS) $(THREAD) map.cpp $(SFML)


clean:
	\rm *.o 

