#include "Window.h"
#include <iostream>
#include <unistd.h>
#include <iomanip>

#define SF_STYLE sf::Style::Titlebar | sf::Style::Close


LEWindow::LEWindow(sf::RenderWindow *lvlWin, sf::RenderWindow *tilWin, sf::RenderWindow *toolWin,
			   const std::string file, const std::string til):
	LvlWindow_(lvlWin), TilWindow_(tilWin), ToolWindow_(toolWin),
	lvl_filename_(file), til_filename_(til),
	currentLayer_(1), currentLive_(0), map_(file)
{
	LvlWindow_->create( sf::VideoMode(LVL_W, LVL_H), "Map editor", SF_STYLE );
	TilWindow_->create( sf::VideoMode(TILE_W, TILE_H), "Tile selector", SF_STYLE );
	ToolWindow_->create( sf::VideoMode( 6*TILE_SIZE, TILE_SIZE ), "Tool", SF_STYLE );
	LvlWindow_->setFramerateLimit( 60 );	
	TilWindow_->setFramerateLimit( 60 );
	ToolWindow_->setFramerateLimit( 60 );


	if (!tileTexture_.loadFromFile( til_filename() ))
	{
		std::cerr << "Fail to load texture " << til_filename() << std::endl ;
		exit( 1 );
	}
	tileSprite_.setTexture( tileTexture_ );
	tileSprite_.setPosition( 0.f, 0.f );

	if (!toolTexture_.loadFromFile( "map-editor-cls/tool_background.png" ))
	{
		std::cerr << "Fail to load texture map-editor-cls/tool_background.png" << std::endl ;
		exit( 1 );
	}
	toolSprite_.setTexture( toolTexture_ );
	toolSprite_.setPosition( 0.f, 0.f );

	if (!font_.loadFromFile("map-editor-cls/font.ttf"))
	{
		std::cerr << "Fail to load font" << std::endl ;
	}

	// test if the level file doesn't exist
	if ( (access( file.c_str(), R_OK|W_OK )) == -1)
	{
		// if so, we create it, empty
		std::ofstream empty_level( file, std::ios::out) ;
		if (empty_level)
		{
			for (int l=0; l<=5; l++)
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

	map_.loadMap( file );
}


LEWindow::~LEWindow(){}

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


void LEWindow::map_draw ()
{
	for (int l=1; l<=4; l++)
		map_.drawMap( l, *LvlWindow_ );
	if ( currentLayer() == 4 )
	{
		char *intStr  ;
		sf::Text text ;
		text.setCharacterSize( 10 );
		text.setFillColor( sf::Color::Red );
		text.setFont( font_ );
		for (int y=0; y<nbTile_H; y++){
			for (int x=0; x<nbTile_W; x++)
			{
				if (map_.getTileBreak( y,x ) != 0)
				{
					std::ostringstream ss;
					int life = map_.getLifeTileBreak( y,x ) ;
					if (life != 0)
					{
						ss << life ;
						text.setPosition( (float) x * TILE_SIZE_f , (float) y * TILE_SIZE_f );
						text.setString( ss.str() );
						LvlWindow_->draw( text );
					}
				}
			}
		}
	}
}


void LEWindow::image_draw() const
{
	TilWindow_->draw( tileSprite_ );

	sf::RectangleShape rect( sf::Vector2f(TILE_SIZE_f, TILE_SIZE_f) );
	rect.setFillColor( sf::Color::Transparent );
	rect.setOutlineThickness( 2.f );
	rect.setOutlineColor( sf::Color::White );
	pair_t pair = posCurrentTile( true ) ;
	rect.setPosition( (float) pair.first * TILE_SIZE_f, (float) pair.second * TILE_SIZE_f );
	TilWindow_->draw( rect );
}


void LEWindow::tool_draw() const
{
	ToolWindow_->draw( toolSprite_ );

	sf::RectangleShape rect( sf::Vector2f(TILE_SIZE_f-2.f, TILE_SIZE_f-2.f) );
	rect.setFillColor( sf::Color::Transparent );
	rect.setOutlineThickness( 2.f );
	rect.setOutlineColor( sf::Color::White );
	pair_t pair = posCurrentTile( true ) ;
	rect.setPosition( OFFSET_X + ((float) currentLayer() - 1.f) * TILE_SIZE_f +1.f, OFFSET_Y + 1.f );
	ToolWindow_->draw( rect );


	sf::Text text ;
	text.setFont( font_ );
	std::ostringstream ss ;
	ss << currentLive_ ;
	text.setString( ss.str() );
	text.setCharacterSize( 10 );
	text.setFillColor( sf::Color::Red );
	text.setPosition( OFFSET_X + 3.f * TILE_SIZE_f + 2.f, OFFSET_Y );

	ToolWindow_->draw( text );
}



void LEWindow::close_windows() const
{
	if (LvlWindow_->isOpen())
		LvlWindow_->close();
	if (TilWindow_->isOpen())
		TilWindow_->close();
	if (ToolWindow_->isOpen())
		ToolWindow_->close();
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
		while (ToolWindow_->pollEvent( event ))
		{
			seekKeyEvent( event );
			seekToolEvent( event );
		}
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			sf::Vector2i position =  sf::Mouse::getPosition( *LvlWindow_ );
			pair_t pair = PairFromPosition( position.x, position.y );
			map_.changeTile( currentLayer(), pair, currentTile() );
			if (currentLayer() == 4)
			{
				map_.setLifeTileBreak( pair.second, pair.first, currentLive_ );
			}
		} else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Right) )
		{
			sf::Vector2i position =  sf::Mouse::getPosition( *LvlWindow_ );
			pair_t pair = PairFromPosition( position.x, position.y );
			map_.changeTile( currentLayer(), pair, 0 );
						if (currentLayer() == 4)
			{
				map_.setLifeTileBreak( pair.second, pair.first, 0 );
			}

		}
		LvlWindow_->clear( sf::Color::Black );
		TilWindow_->clear( sf::Color::Black );
		ToolWindow_->clear( sf::Color::Black );

		map_draw() ;
		image_draw() ;
		tool_draw() ;

		LvlWindow_->display();
		TilWindow_->display();
		ToolWindow_->display();

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
				map_.loadMap( lvl_filename() );
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
			case sf::Keyboard::F :
				fillMap( );
				break ;
			case sf::Keyboard::A :
				if (currentLive_ > 0)
					currentLive_ -- ;
				break ;
			case sf::Keyboard::Z :
				currentLive_ ++ ;
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



void LEWindow::fillMap ()
{
	pair_t pair;
	for (int x=0; x<nbTile_W; x++)
		for (int y=0; y<nbTile_H; y++){
			pair.first = x ; pair.second = y ;
			map_.changeTile( currentLayer(), pair, currentTile() );
			if (currentLayer() == 4)
			{
				map_.setLifeTileBreak( pair.second, pair.first, currentLive_ );
			}
		}
}





void LEWindow::seekLevelEvent( sf::Event event )
{
	pair_t pair = PairFromPosition( event.mouseButton.x, event.mouseButton.y );
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			map_.changeTile( currentLayer(), pair, currentTile() );
			if (currentLayer() == 4)
			{
				map_.setLifeTileBreak( pair.second, pair.first, currentLive_ );
			}
		} else if (event.mouseButton.button == sf::Mouse::Right)
		{
			map_.changeTile( currentLayer(), pair, 0 );
			if (currentLayer() == 4)
			{
				map_.setLifeTileBreak( pair.second, pair.first, 0 );
			}
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


void LEWindow::seekToolEvent( sf::Event event )
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		int x = event.mouseButton.x, y = event.mouseButton.y ;
		if (y >= OFFSET_Y && y <= OFFSET_Y + TILE_SIZE )
		{
			if ( x <= OFFSET_X)
			{
				map_.saveLevel( lvl_filename() );
			} else if ( x >= OFFSET_X && x <= OFFSET_X + 4*TILE_SIZE)	// if we click on one of the four layer
			{
				int l_tmp = PairFromPosition( x - OFFSET_X, y - OFFSET_Y ).first;
				setCurrentLayer( l_tmp + 1 );
			} else if ( x >= OFFSET_X + 4*TILE_SIZE && x <= OFFSET_X + 5*TILE_SIZE)
			{
				if ( y >= OFFSET_Y && y <= OFFSET_Y + TILE_SIZE / 2 )
					currentLive_ ++ ;
				else if (y >= OFFSET_Y + TILE_SIZE / 2 && y <= OFFSET_Y + TILE_SIZE)
					if (currentLive_ > 0)
						currentLive_ -- ;
			}
		}
	}
}





pair_t LEWindow::PairFromPosition(int x, int y) const
{
	pair_t indice ;
	indice.first  = x / TILE_SIZE ;
	indice.second = y / TILE_SIZE ;
	return indice ;
}


int LEWindow::indiceFromPair( pair_t indice, bool tile ) const
{
	int fact = (tile) ? nbTileT_W : nbTile_W ;
	return indice.first + fact*indice.second ;
}


pair_t LEWindow::posCurrentTile(bool tile) const
{
	pair_t pair ;
	pair.first  = (tile) ? currentTile()%nbTileT_W : currentTile()%nbTile_W ;
	pair.second = (tile) ? currentTile()/nbTileT_W : currentTile()/nbTile_W ;
	return pair ;
}