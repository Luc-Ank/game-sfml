#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define screen_W 800
#define screen_H 600

using namespace sf;

class level1
{
public:
    level1(RenderWindow *Mwindow): 
        window(Mwindow){}

    int setForm();
    int setTexture();
    int setCaracter();
    int draw();
    int run_event();

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
};