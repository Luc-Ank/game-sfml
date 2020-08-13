#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "player.hpp"
#include "../Collision/collision.hpp"
using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24
#define Tile_Size 32

#define PLAYERH 64
#define PLAYERW 64
#define START_PLAYER_WALK 7
#define PLAYER_FRAME_MAX 7

Player::Player()
{
    if(!playerTexture.loadFromFile("Images/player.png"))
    {
        std::cout << "Err chargement de l'image du player" << std::endl;
    }
    else
    {
        playerSprite.setTexture(playerTexture);
    }
    /*if(!swordTexture.loadFromFile("Images/sword.png"))
    {
        std::cout << "Err chargement de l'image de l'epée" << std::endl;
    }
    else
    {
        swordSprite.setTexture(swordTexture);
    }
    if(!shieldTexture.loadFromFile("Images/shield.png"))
    {
        std::cout << "Err chargement de l'image du shield" << std::endl;
    }
    else
    {
        shieldSprite.setTexture(shieldTexture);
    }*/

    ghostPlayerX = 0;
    ghostPlayerY = 0;
    life = 100;
    invincibleTimer = 0;
    playerX = 0;
    playerY = 0;
    playerFrameNumber = 0;
    playerFrameTimer = 0;
    playerFrameMax = 0;
    playerEtat = 0;
    playerDirection = 0;
    playerDeathTimer = 0;

    swordTimer = 0;
    swordRotation = 0;
    shieldTimer = 0;
    shieldRotation = 0;

}

Sprite Player::getPlayerSprite(void) const { return playerSprite; }

void Player::drawPlayer(RenderWindow &window)
{
    if (playerFrameTimer <= 0)
    {
        playerFrameTimer = TimeBetween2FramePlayer;
        playerFrameNumber ++;
        if (playerFrameNumber >= playerFrameMax)
        {
            playerFrameNumber = 0;
        }
    }
    else
    {
        if(playerEtat != IDLE)
        {
            playerFrameTimer -= 1 + (playerIsRunning*2);
        }
        else
        {
            //playerFrameTimer --;
        }
    }

    //playerSprite.setPosition(Vector2f(playerX,playerY));

    if(invincibleTimer > 0)
    {
        if(playerFrameNumber % 2 == 0)
        {
            /*playerSprite.setTextureRect(IntRect(,
            playerW,playerH));
            window.draw(playerSprite);*/
        }
    }
    else
    {
        playerSprite.setTextureRect(IntRect(playerFrameNumber*playerW, 
        (playerDirection+START_PLAYER_WALK)*playerH,
        playerW,playerH));
        window.draw(playerSprite);  
        RectangleShape shape(Vector2f(playerW,playerH));//hitboxplayer
        shape.setFillColor(Color::Transparent);
        shape.setPosition(playerX,playerY);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color(250,0,0));
        window.draw(shape);
    }
}

void Player::initPlayer()
{
    life = 100;
    invincibleTimer = 0;

    playerDirection = playerDOWN;
    playerEtat = IDLE;

    playerFrameNumber = 0;
    playerFrameTimer = TimeBetween2FramePlayer;
    playerFrameMax = PLAYER_FRAME_MAX;

    playerX = 0;
    playerY = 0;
    prevPlayerX = 0;
    prevPlayerY = 0;
    playerH = PLAYERH;
    playerW = PLAYERW;
    
    playerCollision = 0;
    playerDeathTimer = 0;
    playerIsAttacking = 0;
}

void Player::updatePlayer(Input &input, Map &map, Monster monster[], int monsterNumber)
{
    if (playerDeathTimer == 0)
    {
        if (invincibleTimer > 0)
        {
            invincibleTimer --;
        }

        ghostPlayerX = 0;
        ghostPlayerY = 0;

        if(input.getButton().run)
            playerIsRunning = 5;
        else
            playerIsRunning = 0;

        if(input.getButton().left == true)
        {
            ghostPlayerX -= playerSpeed + playerIsRunning;
            playerDirection = playerLEFT;

            if(playerEtat != playerWALK)
            {
                playerEtat = playerWALK;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer;
                playerFrameMax = PLAYER_FRAME_MAX;
            }
        }
        else if(input.getButton().right == true)
        {
            ghostPlayerX += playerSpeed + playerIsRunning;
            playerDirection = playerRIGHT;

            if(playerEtat != playerWALK)
            {
                playerEtat = playerWALK;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer;
                playerFrameMax = PLAYER_FRAME_MAX;
            }            
        }
        else if(input.getButton().up == true)
        {
            ghostPlayerY -= playerSpeed + playerIsRunning;
            playerDirection = playerUP;

            if(playerEtat != playerWALK)
            {
                playerEtat = playerWALK;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer;
                playerFrameMax = PLAYER_FRAME_MAX;
            }            
        }
        else if(input.getButton().down == true)
        {
            ghostPlayerY += playerSpeed + playerIsRunning;
            playerDirection = playerDOWN;

            if(playerEtat != playerWALK)
            {
                playerEtat = playerWALK;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer;
                playerFrameMax = PLAYER_FRAME_MAX;
            }            
        }
        else if(input.getButton().right == false && input.getButton().left == false &&
                input.getButton().up == false && input.getButton().down == false)
        {
            if (playerEtat != IDLE)
            {
                playerEtat = IDLE;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer;
                playerFrameMax = PLAYER_FRAME_MAX;
            }
        }

        playerMapCollision(map);
        playerMonsterCollision(monster, input, monsterNumber);
        playerCenterScrolling(map);
    }

    if (playerDeathTimer > 0)
    {
        playerDeathTimer --;
        if (playerDeathTimer == 0)
        {
            //reinit position depart
        }
    }
}


void Player::playerCenterScrolling(Map & map)
{
    int centerPlayerX = playerX + playerW / 2;
    int centerPlayerY = playerY + playerH / 2;
    int xlimmin = 0;
    int xlimmax = screen_W;
    int ylimmin = 0;
    int ylimmax = screen_H;

}

/*void Player::playerMapCollision(Map & map)
{
    int i,x1,x2,y1,y2;

    if(playerH > Tile_Size)
    {
        i = Tile_Size;
    }
    else
    {
        i = playerH;
    }
    
    for(;;)
    {
        x1 = (playerX + ghostPlayerX)/Tile_Size ;
        x2 = (playerX + ghostPlayerX + playerW - 1)/Tile_Size ;

        y1 = (playerY)/Tile_Size ;
        y2 = (playerY + i - 1)/Tile_Size ;   

        if(x1 >= 0 && x2 < screen_W && y1 >= 0 && y2 < screen_H)
        {
            if(ghostPlayerX > 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x2) == MUR1 || map.getTileCollision(y2,x2) == MUR1)
                {
                    playerX = x2*Tile_Size;
                    playerX -= (playerW+1);
                    ghostPlayerX = 0;
                }
                else if (map.getTileBreak(y2,x2) == breakMUR1 || map.getTileBreak(y2,x2) == breakMUR2)
                {
                    playerX = x2*Tile_Size;
                    playerX -= (playerW+1);
                    ghostPlayerX = 0;
                    map.setLifeTileBreak(y2,x2, map.getLifeTileBreak(y2,x2)-1 );
                }
                else if (map.getTileBreak(y1,x2) == breakMUR2 || map.getTileBreak(y1,x2) == breakMUR2)
                {
                    playerX = x2*Tile_Size;
                    playerX -= (playerW+1);
                    ghostPlayerX = 0;
                    map.setLifeTileBreak(y1,x2, map.getLifeTileBreak(y1,x2)-1 );                    
                }
            }
            else if(ghostPlayerX < 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x1) == MUR1 || map.getTileCollision(y2,x1) == MUR1)
                {
                    playerX = (x1+1)*Tile_Size;
                    ghostPlayerX = 0;
                }
                else if (map.getTileBreak(y1,x1) == breakMUR1 || map.getTileBreak(y1,x1) == breakMUR2)
                {
                    playerX = (x1+1)*Tile_Size;
                    ghostPlayerX = 0;
                    map.setLifeTileBreak(y1,x1, map.getLifeTileBreak(y1,x1)-1 );   
                }
                else if (map.getTileBreak(y2,x1) == breakMUR1 || map.getTileBreak(y2,x1) == breakMUR2)
                {
                    playerX = (x1+1)*Tile_Size;
                    ghostPlayerX = 0;
                    map.setLifeTileBreak(y2,x1, map.getLifeTileBreak(y2,x1)-1 );   
                }
            }            
        }
        
        if(i==playerH)
        {
            break;
        }
        i += Tile_Size;

        if(i>playerH)
        {
            i = playerH;
        }    
    }

    if(playerW > Tile_Size)
    {
        i = Tile_Size;
    }
    else
    {
        i = playerW;
    }  
    for(;;)
    {
        x1 = playerX/Tile_Size ;
        x2 = (playerX + i)/Tile_Size ;

        y1 = (playerY + ghostPlayerY)/Tile_Size ;
        y2 = (playerY + ghostPlayerY + playerH)/Tile_Size ;   

        if(x1 >= 0 && x2 < screen_W && y1 >= 0 && y2 < screen_H)
        {
            if(ghostPlayerY > 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y2,x1) == MUR1 || map.getTileCollision(y2,x2) == MUR1)
                {
                    playerY = y2*Tile_Size;
                    playerY -= (playerH+1);
                    ghostPlayerY = 0;
                }
                else if(map.getTileBreak(y2,x1) == breakMUR1 || map.getTileBreak(y2,x1) == breakMUR2)
                {
                    playerY = y2*Tile_Size;
                    playerY -= (playerH+1);
                    ghostPlayerY = 0;
                    map.setLifeTileBreak(y2,x1, map.getLifeTileBreak(y2,x1)-1 );
                }
                else if(map.getTileBreak(y2,x2) == breakMUR1 || map.getTileBreak(y2,x2) == breakMUR2)
                {
                    playerY = y2*Tile_Size;
                    playerY -= (playerH+1);
                    ghostPlayerY = 0;
                    map.setLifeTileBreak(y2,x2, map.getLifeTileBreak(y2,x2)-1 );
                }
            }
            else if(ghostPlayerY < 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x1) == MUR1 || map.getTileCollision(y1,x2) == MUR1)
                {
                    playerY = (y1+1)*Tile_Size;
                    ghostPlayerY = 0;
                }
                else if(map.getTileBreak(y1,x1) == breakMUR1 || map.getTileBreak(y1,x1) == breakMUR2)
                {
                    playerY = (y1+1)*Tile_Size;
                    ghostPlayerY = 0;
                    map.setLifeTileBreak(y1,x1, map.getLifeTileBreak(y1,x1)-1 );
                }
                else if(map.getTileBreak(y1,x2) == breakMUR1 || map.getTileBreak(y1,x2) == breakMUR2)
                {
                    playerY = (y1+1)*Tile_Size;
                    ghostPlayerY = 0;
                    map.setLifeTileBreak(y1,x2, map.getLifeTileBreak(y1,x2)-1 );
                }
            }            
        }
        if(i==playerW)
        {
            break;
        }
        i += Tile_Size;

        if(i>playerW)
        {
            i = playerW;
        }    
    }

    prevPlayerX = playerX;
    prevPlayerY = playerY;
    playerX += ghostPlayerX;
    playerY += ghostPlayerY;

    if(playerX < 0)
    {
        playerX = 0;
    }
    else if (playerX + playerW > screen_W)
    {
        playerX = screen_W - playerW;
    }
    else if(playerY < 0)
    {
        playerY = 0;
    }
    else if (playerY + playerH > screen_H)
    {
        playerY = screen_H - playerH;
    }    
}*/


void Player::playerMapCollision(Map & map)
{
    Sprite testcol;
    int Wtest = (PLAYERW/Tile_Size)+1;
    int Htest = (PLAYERH/Tile_Size)+1;
    int nx,ny;
    nx = (playerX+ghostPlayerX)/Tile_Size;
    ny = (playerY+ghostPlayerY)/Tile_Size;
    //std::cout << playerX << " " << playerY << " " << nx << " " << ny <<  std::endl;
    if(ghostPlayerX > 0)
    {
        for (int i=0; i < Wtest ; i++)
        {
            if (map.getTileCollision(ny+i,nx+2) == MUR1)
            {
                testcol = map.getSprite(ny+i,nx+2);
                playerSprite.setPosition(Vector2f(playerX+ghostPlayerX,playerY+ghostPlayerY));
                if(Collision::PixelPerfectTest(playerSprite,testcol))
                {
                    ghostPlayerX = 0;
                    break;
                }
            }
        }
    }
    else if(ghostPlayerX < 0)
    {
        for (int i=0; i < Wtest ; i++)
        {
            if (map.getTileCollision(ny+i,nx) == MUR1)
            {
                testcol = map.getSprite(ny+i,nx);
                playerSprite.setPosition(Vector2f(playerX+ghostPlayerX,playerY+ghostPlayerY));
                if(Collision::PixelPerfectTest(playerSprite,testcol))
                {
                    ghostPlayerX = 0;
                    break;
                }
            }
        }
    }
    if(ghostPlayerY > 0)
    {
        for (int i=0; i < Htest ; i++)
        {
            if (map.getTileCollision(ny+2,nx+i) == MUR1)
            {
                testcol = map.getSprite(ny+2,nx+i);
                playerSprite.setPosition(Vector2f(playerX+ghostPlayerX,playerY+ghostPlayerY));
                if(Collision::PixelPerfectTest(playerSprite,testcol))
                {
                    ghostPlayerY = 0;
                    break;
                }
            }
        }
    }
    else if(ghostPlayerY < 0)
    {
        for (int i=0; i < Htest ; i++)
        {
            if (map.getTileCollision(ny,nx+i) == MUR1)
            {
                testcol = map.getSprite(ny,nx+i);
                playerSprite.setPosition(Vector2f(playerX+ghostPlayerX,playerY+ghostPlayerY));
                if(Collision::PixelPerfectTest(playerSprite,testcol))
                {
                    ghostPlayerY = 0;
                    break;
                }
            }
        }
    }
    prevPlayerX = playerX;
    prevPlayerY = playerY;
    playerX += ghostPlayerX;
    playerY += ghostPlayerY;
    if(playerX < 0)
    {
        playerX = 0;
    }
    else if (playerX + playerW > screen_W)
    {
        playerX = screen_W - playerW;
    }
    else if(playerY < 0)
    {
        playerY = 0;
    }
    else if (playerY + playerH > screen_H)
    {
        playerY = screen_H - playerH;
    }  
}

void Player::playerMonsterCollision(Monster monster[], Input input, int monsterNumber)
{   
    playerCollision = 0;
    playerSprite.setPosition(Vector2f(playerX,playerY));
    for (int i= 0; i < monsterNumber; i++)
    {
        //if(playerSprite.getGlobalBounds().intersects(monster[i].getMonsterSprite().getGlobalBounds()))
        if (Collision::PixelPerfectTest(playerSprite, monster[i].getMonsterSprite()))
        {
            monster[i].setMonsterStand(0);
            playerCollision = 1;
        }
        else
        {
            monster[i].setMonsterStand(1);
        }
    }
    if(playerCollision)
    {
        playerSprite.setPosition(Vector2f(prevPlayerX,prevPlayerY));
        playerX = prevPlayerX;
        playerY = prevPlayerY;        
    }
    else
    {

        playerSprite.setPosition(Vector2f(playerX,playerY));
    }    
}