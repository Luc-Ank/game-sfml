#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "level1.hpp"

#define screen_W 1024
#define screen_H 768

using namespace sf;

void level1::setForm()
{
    std::cout << " test " << std::endl;
    cercle.setFillColor(Color(250,250,0));
    cercle.setRadius(50);
    cercle.setPosition(700,400);

    rectangle.setFillColor(Color(250,250,0));
    rectangle.setSize(Vector2f(50,100));
    rectangle.setPosition(120,230);
    //srectangle.setRotation(30);

    cercle.setOutlineColor(Color(0,250,250));
    cercle.setOutlineThickness(10);
    //shape.setFillColor(Color::Green);
}

void level1::setCaracter()
{
	player.initPlayer();
}

void level1::setTexture()
{
	std::string filename;
	filename = "Map/map1.txt";
	map.changeLevel(filename);
}

void level1::draw()
{
	window->clear();
	map.drawMap(1,*window);
	map.drawMap(2,*window);
	map.drawMap(3,*window);
	player.drawPlayer(*window);
    //window->draw(background);
	window->draw(cercle);
	window->draw(rectangle);
	window->draw(sprite_perso);
}

void level1::run_event(Input &input)
{
	input.gestionInputs(*window);
	player.updatePlayer(input, map);
}