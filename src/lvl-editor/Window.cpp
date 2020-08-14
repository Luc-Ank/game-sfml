#include "Window.h"
#include <iostream>
#include <unistd.h>

#define SF_STYLE sf::Style::Titlebar | sf::Style::Close


LEWindow::LEWindow(sf::RenderWindow *lvlWin, sf::RenderWindow *tilWin,
			   const std::string file, const std::string til):
	LvlWindow_(lvlWin), TilWindow_(tilWin),
	lvl_filename_(file), til_filename_(til),
	currentLayer_(1)
{
	LvlWindow_->create( sf::VideoMode(LVL_W, LVL_H), "Level editor", SF_STYLE );
	TilWindow_->create( sf::VideoMode(TILE_W, TILE_H), "Tile selector", SF_STYLE );
	LvlWindow_->setFramerateLimit( 60 );	
	TilWindow_->setFramerateLimit( 60 );


	if (!tileTexture_.loadFromFile( til_filename() ))
	{
		std::cerr << "raler" << std::endl ;
		exit( 1 );
	}
	tileSprite_.setTexture( tileTexture_ );
	tileSprite_.setPosition( 0.f, 0.f );

	// test if the level file doesn't exist
	if ( (access( file.c_str(), R_OK|W_OK )) == -1)
	{
		// if so, we create it, empty
		std::ofstream empty_level( file, std::ios::out) ;
		if (empty_level)
		{
			for (int l=0; l<4; l++)
			{
				for (int y=0; y<nbTile_H; y++)
				{
					for (int x=0; x<nbTile_W-1; x++)
					{
						empty_level << "0," ;
					}
					empty_level << "0" << std::endl ;
				}
				empty_level << std::endl ;
			}
		} else
		{
			std::cerr << "Fail to open " << file << std::endl ;
			exit( 0 );
		}
	}

	map_.loadMap( file, false );
}


LEWindow::~LEWindow(){
	// std::cout << "Destruction" << std::endl ;
}

std::string LEWindow::lvl_filename() const { return lvl_filename_ ; }
std::string LEWindow::til_filename() const { return til_filename_ ; }
int LEWindow::currentLayer() const { return currentLayer_ ; }
int LEWindow::currentTile() const { return currentTile_ ; }



void LEWindow::setCurrentLayer (int i)
{
	if (i==1 || i==2 || i==3 || i==4 )
	{
		std::cout << "Current layer is now " << i << std::endl ;
		currentLayer_ = i ;
	} else
	{
		std::cout << "Bad value for layer (" << i << ")" << std::endl ;
	}
}
void LEWindow::setCurrentTile (int i) { currentTile_ = i ;}

void LEWindow::image_draw() const
{
	TilWindow_->draw( tileSprite_ );

	sf::RectangleShape rect( sf::Vector2f(TILE_SIZE_f, TILE_SIZE_f) );
	rect.setFillColor( sf::Color::Transparent );
	rect.setOutlineThickness( 2.f );
	rect.setOutlineColor( sf::Color::White );
	std::pair<int,int> pair = posCurrentTile( true ) ;
	rect.setPosition( (float) pair.first * TILE_SIZE_f, (float) pair.second * TILE_SIZE_f );
	TilWindow_->draw( rect );
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
			seekKeyEvent( event );
			seekLevelEvent( event );
		}
		while (TilWindow_->pollEvent( event ))
		{
			seekKeyEvent( event );
			seekTileEvent( event );
		}
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			sf::Vector2i position =  sf::Mouse::getPosition( *LvlWindow_ );
			std::pair<int,int> pair = PairFromPosition( position.x, position.y );
			map_.changeTile( currentLayer(), pair, currentTile() );
		} else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Right) )
		{
			sf::Vector2i position =  sf::Mouse::getPosition( *LvlWindow_ );
			std::pair<int,int> pair = PairFromPosition( position.x, position.y );
			map_.changeTile( currentLayer(), pair, 0 );

		}
		LvlWindow_->clear( sf::Color::Black );
		TilWindow_->clear( sf::Color::Black );

		for (int l=1; l<=4; l++)
			map_.drawMap( l, *LvlWindow_ );
		image_draw();

		LvlWindow_->display();
		TilWindow_->display();

	}
}









void LEWindow::seekKeyEvent(sf::Event event)
{
	if ( (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
				|| (event.type == sf::Event::Closed) )
	{
		close_windows();
	} else if (event.type == sf::Event::KeyPressed){
		switch (event.key.code)
		{
			case sf::Keyboard::S :
				map_.saveLevel( lvl_filename() );
				break ;
			case sf::Keyboard::R :
				map_.loadMap( lvl_filename(), false );
				break ;
			case sf::Keyboard::F1 :
				setCurrentLayer( 1 );
				break ;
			case sf::Keyboard::F2 :
				setCurrentLayer( 2 );
				break ;
			case sf::Keyboard::F3 :
				setCurrentLayer( 3 );
				break ;
			case sf::Keyboard::F4 :
				setCurrentLayer( 4 );
				break ;
			default :
				break ;
		}
	} /*else if (event.type ==sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{

			default :
				break ;
		}
	}*/
}



void LEWindow::seekLevelEvent( sf::Event event )
{
	std::pair<int,int> pair = PairFromPosition( event.mouseButton.x, event.mouseButton.y );
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			map_.changeTile( currentLayer(), pair, currentTile() );
		} else if (event.mouseButton.button == sf::Mouse::Right)
		{
			map_.changeTile( currentLayer(), pair, 0 );
		}
	}
}


void LEWindow::seekTileEvent( sf::Event event )
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			setCurrentTile( indiceFromPair( PairFromPosition( event.mouseButton.x, event.mouseButton.y ), true ) );
		} /*else if (event.mouseButton.button == sf::Mouse::Right)
		{

		}*/
	}
}



std::pair<int,int> LEWindow::PairFromPosition(int x, int y) const
{
	std::pair<int,int> indice ;
	indice.first  = x / TILE_SIZE ;
	indice.second = y / TILE_SIZE ;
	return indice ;
}


int LEWindow::indiceFromPair( std::pair<int,int> indice, bool tile ) const
{
	int fact = (tile) ? nbTileT_W : nbTile_W ;
	return indice.first + fact*indice.second ;
}


std::pair<int,int> LEWindow::posCurrentTile(bool tile) const
{
	std::pair<int,int> pair ;
	pair.first  = (tile) ? currentTile()%nbTileT_W : currentTile()%nbTile_W ;
	pair.second = (tile) ? currentTile()/nbTileT_W : currentTile()/nbTile_W ;
	return pair ;
}