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
#include "../Collision/collision.hpp"

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
        void updateMonster(std::string action, Map &map, Monster monster[], int monsterNumber, int actualmonster);
        //void playerCenterScrolling(Map &map);
        void monsterMapCollision(Map &map);
        void monsterMonsterCollision(Monster monster[], int monsterNumber, int actualmonster);

        int getMonsterH(void) const;
        int getMonsterW(void) const;
        int getMonsterX(void) const;
        int getMonsterY(void) const;
        int getPrevMonsterX(void) const;
        int getPrevMonsterY(void) const;        
        int getGhostMonsterX(void) const;
        int getGhostMonsterY(void) const;
        bool getMonsterStand(void) const;
        Sprite getMonsterSprite(void) const;
        int getMonsterLife(void) const;
        int getIsGettingDamage(void) const;
        int getMonsterIsAlive(void) const;

        void setMonsterStand(int valeur);
        void setMonsterLife(int valeur);
        void setIsGettingDamage(int valeur);
        void setMonsterIsAlive(int valeur);
        void setMonsterX(int valeur);
        void setMonsterY(int valeur);

    protected:
        int monsterLife,monsterLifeMax;
        int isGettingDamage;
        int monsterIsAlive;
        int monsterDeadAnimation;

        int monsterX,monsterY;
        int monsterW,monsterH;
        int monsterFrameNumber, monsterFrameTimer, monsterFrameMax;
        int prevMonsterFrameNumber;

        int monsterIsRunning,monsterIsAttacking;
        int monsterEtat,monsterDirection;

        int ghostMonsterX,ghostMonsterY;
        int prevMonsterX,prevMonsterY;
        int prevMonsterDirection;

        int monsterStand;

        Texture monsterTexture;
        Sprite monsterSprite;

        const int TimeBetween2FrameMonster = 3;
        const int TimeBetween2FrameSword = 1;

        const int monsterSpeed = 5;

        const int IDLE = 0;
        const int monsterWALK = 1;
        const int monsterDEAD = 4;

        const int monsterUP = 1;
        const int monsterLEFT = 2;
        const int monsterDOWN = 3;
        const int monsterRIGHT = 4;

        enum{up,down,right,left,attack,run,protect};

        const int MUR1 = 42;
        const int breakMUR1 = 282;
        const int breakMUR2 = 288;
};
#endif