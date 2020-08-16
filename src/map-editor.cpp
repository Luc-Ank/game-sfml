#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <mutex>


#include "map-editor-cls/Window.h"



int main (int argc, char ** argv)
{
	std::cout << argc << std::endl ;
	if (argc != 2 && argc != 3 && argc != 4)
	{
		std::cerr << "usage : " << argv[0] << " level-filename [tile-file1 tile-file2]" << std::endl ;
		exit( 1 );
	}
	std::string tile1 = (argc >= 3) ? argv[2] : "" ;
	std::string tile2 = (argc == 4) ? argv[3] : tile1 ;

	sf::RenderWindow mapRenderWindow, tileRenderWindow, toolRenderWindow;

	MEWindow win( &mapRenderWindow, &tileRenderWindow, &toolRenderWindow, argv[1], tile1, tile2 );

	// handle the window
	win.Run();


	return 0 ;
}