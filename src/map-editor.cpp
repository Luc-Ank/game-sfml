#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <mutex>


#include "map-editor-cls/Window.h"



int main (int argc, char ** argv)
{
	if (argc != 3)
	{
		std::cerr << "usage : " << argv[0] << " level-filename tile-file" << std::endl ;
		exit( 1 );
	}

	sf::RenderWindow mapRenderWindow, tileRenderWindow, toolRenderWindow;

	MEWindow win( &mapRenderWindow, &tileRenderWindow, &toolRenderWindow, argv[1], argv[2] );

	// handle the window
	win.Run();


	return 0 ;
}