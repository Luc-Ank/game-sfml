#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "level1.hpp"

#define screen_W 1024
#define screen_H 768

using namespace sf;

enum Dir {Down,Left,Right,Up};

void gestion_clavier(Sprite *sprite_perso, Vector2i *anim){
	if(Keyboard::isKeyPressed(Keyboard::Up)){
		anim->y = Up;
		sprite_perso->move(0,-5);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Down)){
		anim->y = Down;
		sprite_perso->move(0,5);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Left)){
		anim->y = Left;
		sprite_perso->move(-5,0);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Right)){
		anim->y = Right;
		sprite_perso->move(5,0);
	}
	if(sprite_perso->getPosition().x <= 0)
		sprite_perso->setPosition(Vector2f(0,sprite_perso->getPosition().y));
    else if(sprite_perso->getPosition().x >= screen_W-32)
		sprite_perso->setPosition(Vector2f(screen_W-32,sprite_perso->getPosition().y));
	if(sprite_perso->getPosition().y <= 0)
		sprite_perso->setPosition(Vector2f(sprite_perso->getPosition().x,0));
	else if(sprite_perso->getPosition().y >= screen_H-138)
		sprite_perso->setPosition(Vector2f(sprite_perso->getPosition().x,screen_H-138));
}


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
    if(!perso.loadFromFile("Images/boss.png"))
    {
		std::cout<< "Err chargement boss.png" << std::endl;
    }
    perso.setSmooth(true); //lisser la texture::gourmant
    sprite_perso.setTexture(perso);
    anim.x=1;
    anim.y=Down;
}

void level1::setTexture()
{
    /*if(!backgroundTexture.loadFromFile("Images/back1.png"))
    {
		std::cout<< "Err chargement boss.png" << std::endl;
	}
	background.setTexture(backgroundTexture);*/

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
    //window->draw(background);
	window->draw(cercle);
	window->draw(rectangle);
	window->draw(sprite_perso);
}

void level1::run_event()
{
    while (window->pollEvent(event))
	{
		if(event.type == Event::Closed)
			window->close();
		if(event.type == Event::KeyPressed)
		{
			updateFPS = true;
		}
		else
			updateFPS = false;
	}
	    
	lpos.x = sprite_perso.getPosition().x;
	lpos.y = sprite_perso.getPosition().y;

    gestion_clavier(&sprite_perso, &anim);

    if(updateFPS == true){
		if(time.getElapsedTime().asMilliseconds() >= 200){
			anim.x --;
			if(anim.x * 32 >= perso.getSize().x)
				anim.x = 2;
				time.restart();
		}
	}
	sprite_perso.setTextureRect(IntRect(anim.x *32, anim.y * 32,32,32));

    //collision 
	if(sprite_perso.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
	{
		std::cout << " dddd " << std::endl;
		sprite_perso.setPosition(Vector2f(lpos.x,lpos.y));
	}

	/*position.x = sprite_perso.getPosition().x;
	position.y = sprite_perso.getPosition().y ;
	std::cout << position.x << " " << position.y << std::endl;*/

    //vue
    /*view.reset(FloatRect(0,0,screen_W,screen_H));

	position.x = sprite_perso.getPosition().x + 16 - screen_W/2;
	position.y = sprite_perso.getPosition().y + 16 - screen_H/2;
	std::cout << position.x << " " << position.y << std::endl;
	if(position.x < 0)
	    position.x = 0;
	if(position.y < 0)
		position.y = 0;
    if(position.x > screen_H)
	    position.x = screen_H;
	if(position.y > screen_W)
		position.y = screen_W;
    
	view.reset(FloatRect(position.x,position.y,screen_W,screen_H));
	window->setView(view);*/
}