#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Map/map.hpp"

using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24

class Monster
{
    public:
        Monster();

        void drawMonster(RenderWindow &window);
        void initMonster(int x, int y); 
        void updateMonster(std::string action, Map &map);
        //void playerCenterScrolling(Map &map);
        void monsterMapCollision(Map &map);

    protected:
        int life;

        int monsterX,monsterY;
        int monsterW,monsterH;
        int monsterFrameNumber, monsterFrameTimer, monsterFrameMax;

        int monsterIsRunning,monsterIsAttacking;
        int monsterEtat,monsterDirection;

        int ghostMonsterX,ghostMonsterY;
        int prevMonsterX,prevMonsterY;

        Texture monsterTexture;
        Sprite monsterSprite;

        const int TimeBetween2FrameMonster = 3;
        const int TimeBetween2FrameSword = 1;

        const int monsterSpeed = 5;

        const int IDLE = 0;
        const int monsterWALK = 1;
        const int monsterDEAD = 4;

        const int monsterDOWN = 3;
        const int monsterLEFT = 2;
        const int monsterRIGHT = 4;
        const int monsterUP = 1;

        enum{up,down,right,left,attack,run,protect};

        const int MUR1 = 42;
        const int breakMUR1 = 282;
        const int breakMUR2 = 288;
};
#endif