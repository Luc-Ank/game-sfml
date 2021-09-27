#ifndef SPELL_H
#define SPELL_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Input/input.hpp"
#include "../Map/map.hpp"
#include "../Monster/monster.hpp"

using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24



class Spell
{
    public:
        void addSpell(int playerX, int playerY, int playerDirection);
        void updateSpell();
        void initSpell();
        void drawSpell(RenderWindow &window);
        void spellMonsterCollision(Monster monster[], int monsterNumber);

    private:
        static const int maxNumberOfSpell = 20;

        const int playerUP = 1;
        const int playerLEFT = 2;
        const int playerDOWN = 3;
        const int playerRIGHT = 4;

        int spellList[maxNumberOfSpell][4]; //x,y,direction,activé
        Texture spellTexture1;
        Sprite spellSprite1;
        Sprite spellSprite[maxNumberOfSpell];

        int numberOfSpell;
};

#endif