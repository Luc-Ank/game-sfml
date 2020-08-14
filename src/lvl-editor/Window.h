#ifndef WIN_H
#define WIN_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "../Map/map.hpp"

#define TILE_W		320
#define TILE_H		1280
#define LVL_W 		1024
#define LVL_H		768
#define nbTile_W 	32
#define nbTile_H 	24
#define nbTileT_W	10
#define TILE_SIZE	32
#define TILE_SIZE_f	32.f

class LEWindow
{
public:
	// Constructor
	LEWindow(sf::RenderWindow *, sf::RenderWindow *,
		   const std::string, const std::string);

	// Accessors
	std::string lvl_filename() const;
	std::string til_filename() const;
	int currentLayer() const;
	int currentTile() const;

	// Mutators
	void setCurrentLayer(int);
	void setCurrentTile(int);

	// Draw the tile set on the window
	void image_draw() const;
	// Close all windows
	void close_windows() const;

	// Run the application
	// in a concerned application : bool correspond to if we are in the tile
	// 	window or not
	void Run();
	void seekKeyEvent(sf::Event) ;
	void seekMouseLevelEvent(sf::Event) ;
	void seekMouseTileEvent(sf::Event) ;
	std::pair<int,int> PairFromPosition(int, int) const ;
	int indiceFromPair(std::pair<int,int>, bool) const ;
	std::pair<int,int> posCurrentTile(bool) const ;

private:
	int currentLayer_, currentTile_ ;
	// bool multiple_ ;
	sf::RenderWindow *LvlWindow_, *TilWindow_ ;
	std::string lvl_filename_, til_filename_ ;
	sf::Texture tileTexture_ ;
	sf::Sprite  tileSprite_; 
	Map map_ ;
};


#endif
