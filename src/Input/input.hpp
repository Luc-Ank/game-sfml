#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24
#define playerHW 32


class Input
{
    struct Button{bool up,down,right,left,attack,run,enter,protect,switchDagger,switchSpear,spell;};

    public:
        Input();

        Button getButton(void) const;

        void setButton(int bouton, bool etat);

        void gestionInputs(RenderWindow &window);
        void getInput(RenderWindow &window);
    protected:
        Event event;
        Button button;

        enum{up,down,right,left,attack,run,enter,protect,switchDagger,switchSpear,spell};
};
#endif