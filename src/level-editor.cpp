#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <mutex>


#include "lvl-editor/Window.h"



int main (int argc, char ** argv)
{
	if (argc != 3)
	{
		std::cerr << "usage : " << argv[0] << " level-filename tile-file" << std::endl ;
		exit( 1 );
	}

	sf::RenderWindow levelRenderWindow, tileRenderWindow;

	LEWindow win( &levelRenderWindow, &tileRenderWindow, argv[1], argv[2] );

	// handle the window
	win.Run();


	return 0 ;
}