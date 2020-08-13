#include "Window.h"
#include <iostream>
#include <unistd.h>


LEWindow::LEWindow(sf::RenderWindow *lvlWin, sf::RenderWindow *tilWin,
			   const std::string file, const std::string til):
	LvlWindow_(lvlWin), TilWindow_(tilWin),
	lvl_filename_(file), til_filename_(til)
{
	LvlWindow_->create( sf::VideoMode(LVL_W, LVL_H), "Level editor" );
	TilWindow_->create( sf::VideoMode(TILE_W, TILE_H), "Tile selector" );
	LvlWindow_->setFramerateLimit( 60 );	
	TilWindow_->setFramerateLimit( 60 );

	// test if the level file doesn't exist
	if ( (access( file.c_str(), R_OK|W_OK )) == -1)
	{
		// if so, we create it, empty
		std::ofstream empty_level( file, std::ios::out) ;
		for (int l=0; l<4; l++)
		{
			for (int y=0; y<nbTile_H; y++)
			{
				for (int x=0; x<nbTile_W-1; x++)
				{
					empty_level << "1," ;
				}
				empty_level << "0" << std::endl ;
			}
			empty_level << std::endl ;
		}
	}

	map_.loadMap( file, false );
}

std::string LEWindow::lvl_filename() const
{
	return lvl_filename_ ;
}

std::string LEWindow::til_filename() const
{
	return til_filename_ ;
}




void LEWindow::image_draw() const
{
	sf::Texture text ;
	if (!text.loadFromFile( til_filename() ))
	{
		std::cerr << "raler" << std::endl ;
		exit( 1 );
	}
	sf::Sprite sprite ;
	sprite.setTexture( text );
	sprite.setPosition( 0.f, 0.f );
	TilWindow_->draw( sprite );
}



void LEWindow::close_windows() const
{
	if (LvlWindow_->isOpen())
		LvlWindow_->close();
	if (TilWindow_->isOpen())
		TilWindow_->close();
}






void LEWindow::Run()
{
	while (LvlWindow_->isOpen())
	{
		sf::Event event;
		while (LvlWindow_->pollEvent( event ))
		{
			if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
				|| (event.type == sf::Event::Closed) )
			{
				close_windows();
			}
		}
		while (TilWindow_->pollEvent( event ))
		{
			if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
				|| (event.type == sf::Event::Closed) )
			{
				close_windows();
			}
		}

		LvlWindow_->clear( sf::Color::Black );
		TilWindow_->clear( sf::Color::Black );

		for (int l=0; l<4; l++)
			map_.drawMap( l, *LvlWindow_ );
		image_draw();

		LvlWindow_->display();
		TilWindow_->display();

	}
}