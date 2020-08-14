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
#define OFFSET_X	0
#define OFFSET_Y	0


using pair_t = std::pair<int,int>;

class LEWindow
{
public:
	// Constructor
	LEWindow(sf::RenderWindow *, sf::RenderWindow *, sf::RenderWindow *,
		   const std::string, const std::string);
	~LEWindow();

	// Accessors
	std::string lvl_filename() const;
	std::string til_filename() const;
	int currentLayer() const;
	int currentTile() const;

	// Mutators
	void setCurrentLayer(int);
	void setCurrentTile(int);

	void fillMap();

	// Draw the tile set on the window
	void image_draw() const;
	void tool_draw() const;
	// Close all windows
	void close_windows() const;

	// Run the application
	// in a concerned application : bool correspond to if we are in the tile
	// 	window or not
	void Run();
	void seekKeyEvent(sf::Event) ;
	void seekLevelEvent(sf::Event) ;
	void seekTileEvent(sf::Event) ;
	void seekToolEvent(sf::Event) ;
	pair_t PairFromPosition(int, int) const ;
	int indiceFromPair(pair_t, bool) const ;
	pair_t posCurrentTile(bool) const ;

private:
	int currentLayer_, currentTile_ ;
	sf::RenderWindow *LvlWindow_, *TilWindow_, *ToolWindow_ ;
	std::string lvl_filename_, til_filename_ ;
	sf::Texture tileTexture_ ;//, toolTexture_ ;
	sf::Sprite  tileSprite_  ;//, toolSprite_ ; 
	Map map_ ;
};


#endif
