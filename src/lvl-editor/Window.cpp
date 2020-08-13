#include "Window.h"


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
				LvlWindow_->close();
				if (TilWindow_->isOpen())
					TilWindow_->close();
			}	
		}
		while (TilWindow_->pollEvent( event ))
		{
			if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
				|| (event.type == sf::Event::Closed) )
			{
				TilWindow_->close();
				if (LvlWindow_->isOpen())
					LvlWindow_->close();
			}	
		}

		LvlWindow_->clear( sf::Color::Black );
		TilWindow_->clear( sf::Color::Black );

		// image.draw();

		LvlWindow_->display();
		TilWindow_->display();

	}
}