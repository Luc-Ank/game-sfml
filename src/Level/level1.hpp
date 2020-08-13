#ifndef LEVEL1_H
#define LEVEL1_H

#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Player/player.hpp"
#include "../Monster/monster.hpp"
#include "../Map/map.hpp"
#include "../Input/input.hpp"

using namespace sf;

class level1
{
public:
    level1(RenderWindow *Mwindow): 
        window(Mwindow){}

    void setForm();
    void setTexture();
    void setCaracter();
    void setMonster();
    void draw();
    void run_event(Input &input);

protected:
    RenderWindow *window;
    CircleShape cercle;
    RectangleShape rectangle;

    Texture perso;
    Sprite sprite_perso;
	Texture backgroundTexture;
	Sprite background;

    Event event;
    Clock time;
    View view;

    bool updateFPS;
    Vector2f lpos;
    Vector2f position;
    Vector2i anim;

    Map map;
    Player player;
    Monster monster[3];
};
#endif