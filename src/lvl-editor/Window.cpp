#include "Window.h"
#include <iostream>


Window::Window(sf::RenderWindow *lvlWin, sf::RenderWindow *tilWin,
			   const std::string file, const std::string til):
	LvlWindow_(lvlWin), TilWindow_(tilWin),
	lvl_filename_(file), til_filename_(til)
{
	LvlWindow_->create( sf::VideoMode(LVL_W, LVL_H), "Level editor" );
	TilWindow_->create( sf::VideoMode(TILE_W, TILE_H), "Tile selector" );
	LvlWindow_->setFramerateLimit( 60 );	
	TilWindow_->setFramerateLimit( 60 );
}

std::string Window::lvl_filename() const
{
	return lvl_filename_ ;
}

std::string Window::til_filename() const
{
	return til_filename_ ;
}




void Window::image_draw() const
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



void Window::close_windows() const
{
	if (LvlWindow_->isOpen())
		LvlWindow_->close();
	if (TilWindow_->isOpen())
		TilWindow_->close();
}






void Window::Run()
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

		// level.draw();
		image_draw();

		LvlWindow_->display();
		TilWindow_->display();

	}
}