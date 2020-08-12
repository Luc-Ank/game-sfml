#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>


#include "lvl-editor/levelWindow.h"
#include "lvl-editor/tileWindow.h"


int main (int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cerr << "usage : " << argv[0] << " tile-file" << std::endl ;
		exit( 1 );
	}

	sf::RenderWindow levelWindow, tileWindow;

	// handle the level window
 
	// handle the tile window

	return 0 ;
}