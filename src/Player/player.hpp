#ifndef PLAYER_H
#define PLAYER_H

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

class Player
{
    public:
        Player();

        void drawPlayer(RenderWindow &window);
        void initPlayer(); 
        void updatePlayer(Input &input, Map &map, Monster monster[], int monsterNumber);
        void playerCenterScrolling(Map &map);
        void playerMapCollision(Map &map);
        void playerMonsterCollision(Monster monster[], Input input, int monsterNumber);

    protected:
        int life;
        int invincibleTimer;

        int playerX,playerY;
        int playerW,playerH;
        int playerFrameNumber, playerFrameTimer, playerFrameMax;

        int playerIsRunning,playerIsAttacking;
        int playerEtat,playerDirection;

        int playerDeathTimer;
        int ghostPlayerX,ghostPlayerY;
        int prevPlayerX,prevPlayerY;

        int playerCollision;

        Texture playerTexture;
        Sprite playerSprite;
        Texture swordTexture;
        Sprite swordSprite;
        Texture shieldTexture;
        Sprite shieldSprite;

        int swordX,wordY,swordTimer,swordRotation;
        int shieldX,shieldY,shieldTimer,shieldRotation;

        const int TimeBetween2FramePlayer = 3;
        const int TimeBetween2FrameSword = 1;
        const int TimeBetween2FrameShield = 1;

        const int playerSpeed = 5;

        const int IDLE = 0;
        const int playerWALK = 1;
        const int playerDEAD = 4;

        const int playerDOWN = 0;
        const int playerLEFT = 1;
        const int playerRIGHT = 2;
        const int playerUP = 3;

        enum{up,down,right,left,attack,run,enter,protect};

        const int MUR1 = 42;
        const int breakMUR1 = 282;
        const int breakMUR2 = 288;
};

#endif