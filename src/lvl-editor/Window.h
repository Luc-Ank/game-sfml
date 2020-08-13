#ifndef WIN_H
#define WIN_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#define TILE_W 320
#define TILE_H 1280

#define LVL_W 1024
#define LVL_H 768

class Window
{
public:
	Window(sf::RenderWindow *, sf::RenderWindow *,
		   const std::string, const std::string);
	std::string lvl_filename() const;
	std::string til_filename() const;

	void Run();

private:
	sf::RenderWindow *LvlWindow_, *TilWindow_ ;
	std::string lvl_filename_, til_filename_ ;
};


#endif