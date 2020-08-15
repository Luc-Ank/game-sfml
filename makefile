CC = g++
CFLAGS = -c
# DEBUG = -Wall -Werror -Wextra
# THREAD = -pthread
SFML = -lsfml-graphics -lsfml-window -lsfml-system

# all: game-sfml

# #debug: all

# game-sfml: test.o Level/level1.o 
# 	$(CC) $(THREAD) test.o  Level/level1.o -o game-sfml $(SFML)

# test.o: test.cpp Level/level1.o
# 	$(CC) $(CFLAGS) test.cpp Level/level1.o  $(SFML)

# /Level/level1.o: Level/level1.cpp Level/level1.hpp Player/player.o
# 	$(CC) $(CFLAGS) Level/level1.cpp Player/player.o  $(SFML)

# /Player/player.o: Player/player.cpp Player/player.hpp Input/input.o Map/map.o
# 	$(CC) $(CFLAGS) Input/input.o Map/map.o Player/player.cpp  $(SFML)

# /Map/map.o: Map/map.cpp Map/map.hpp Map/map1.txt
# 	$(CC) $(CFLAGS) $(THREAD) Map/map.cpp $(SFML)

# /Input/input.o: Input/input.cpp Input/input.hpp
# 	$(CC) $(CFLAGS) $(THREAD) Input/input.cpp $(SFML)


# clean:
# 	\rm *.o game-sfml

# run: all
# run:
# 	./game-sfml


DIRS = src/Collision src/Map src/Input src/Monster src/Player src/Level src/map-editor-cls src
BUILDDIRS = $(DIRS:%=build-%)
CLEANDIR = $(DIRS:%=clean-%)

all: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

clean: $(CLEANDIR)
$(CLEANDIR):
	$(MAKE) -C $(@:clean-%=%)

.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(BUILDDIRS)
.PHONY: subdirs $(CLEANDIR)	
