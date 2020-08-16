#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Level/level1.hpp"


using namespace sf;

#define screen_W 1024
#define screen_H 768

int main()
{
    RenderWindow window;
    window.create(VideoMode(screen_W,screen_H),"SFML works"); //Style::Fullscreen  no
	window.setFramerateLimit(60);

    level1 level(&window, "Map/map1.txt");
    std::cout << " Fenetre crée " << std::endl;

    level.setForm();
    std::cout << " Forme crée " << std::endl;

    level.setCaracter();
    level.setTexture();

    while(window.isOpen())
    {
        window.display();
        level.run_event();
        level.draw();
    }
}