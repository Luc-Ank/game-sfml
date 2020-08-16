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
#define START_PLAYER_DEAD 20
#define PLAYER_FRAME_DEAD 6
#define START_PLAYER_WALK 7
#define PLAYER_FRAME_MAX 7
#define START_PlAYER_ATTACK_SPEAR 3
#define PlAYER_FRAME_ATTACK_SPEAR 8
#define START_PlAYER_ATTACK_DAGGER 11
#define PlAYER_FRAME_ATTACK_DAGGER 6

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
    if(!daggerTexture.loadFromFile("Images/playerDagger.png"))
    {
        std::cout << "Err chargement de l'image de l'dagger" << std::endl;
    }
    else
    {
        daggerSprite.setTexture(daggerTexture);
    }
    if(!spearTexture.loadFromFile("Images/playerSpear.png"))
    {
        std::cout << "Err chargement de l'image du spear" << std::endl;
    }
    else
    {
        spearSprite.setTexture(spearTexture);
    }

    ghostPlayerX = 0;
    ghostPlayerY = 0;
    playerLife = 100;
    playerLifeMax = 100;
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
    //playerSprite.setPosition(Vector2f(playerX,playerY));
    if (playerDeathTimer == 0)
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
            if(playerEtat != IDLE || playerIsAttacking == 1)
            {
                playerFrameTimer -= 1 + (playerIsRunning*2) + (playerIsAttacking*3);
            }
            else
            {
                //playerFrameTimer --;
            }
        }

        playerSprite.setTextureRect(IntRect(playerFrameNumber*playerW, 
        (playerDirection+startPlayerState)*playerH,
        playerW,playerH));
        window.draw(playerSprite);  
        RectangleShape shape(Vector2f(playerW,playerH));//hitboxplayer
        shape.setFillColor(Color::Transparent);
        shape.setPosition(playerX,playerY);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color(250,0,0));
        window.draw(shape);

        RectangleShape playerLifeBar(Vector2f(PLAYERW,8));//playerLifeBar
        RectangleShape playerLifeBarInside(Vector2f(PLAYERW*(float(playerLife)/playerLifeMax),8));
        playerLifeBarInside.setFillColor(Color::Red);
        playerLifeBarInside.setPosition(playerX,playerY);
        playerLifeBar.setFillColor(Color::Transparent);
        playerLifeBar.setPosition(playerX,playerY);
        playerLifeBar.setOutlineThickness(2);
        playerLifeBar.setOutlineColor(Color(0,0,0));
        window.draw(playerLifeBar);
        window.draw(playerLifeBarInside);
    }
    else
    {
        //prevMPlayerFrameNumber = playerFrameNumber;
        if (playerFrameTimer <= 0)
        {
            playerFrameTimer = TimeBetween2FramePlayer;
            playerFrameNumber ++;
        }
        else
        {
            playerFrameTimer -= 1 ;
        }

        //monsterSprite.setPosition(Vector2f(monsterX,monsterY)); //????
        playerSprite.setTextureRect(IntRect(playerFrameNumber*playerW, 
        (START_PLAYER_DEAD)*playerH,
        playerW,playerH));
        window.draw(playerSprite); 
        if (playerFrameNumber >= playerFrameMax)
        {
            initPlayer();
        }        
    }
    
}

void Player::initPlayer()
{
    playerLife = 100;
    playerLifeMax = 100;
    invincibleTimer = 0;

    playerDirection = playerDOWN;
    playerEtat = IDLE;

    playerFrameNumber = 0;
    playerFrameTimer = TimeBetween2FramePlayer;
    playerFrameMax = PLAYER_FRAME_MAX;

    daggerOn = 0;
    spearOn = 0;
    changeSpearState = 1;
    changeDaggerState = 1;
    playerX = 0;
    playerY = 0;
    prevPlayerX = 0;
    prevPlayerY = 0;
    playerH = PLAYERH;
    playerW = PLAYERW;
    
    playerCollision = 0;
    playerDeathTimer = 0;
    playerIsAttacking = 0;

    playerSprite.setTexture(playerTexture);
}

void Player::updatePlayer(Input &input, Map &map, Monster monster[], int monsterNumber)
{
    for (int i = 0; i < monsterNumber; i++)
    {
        if (monster[i].getPlayerIsGettingDmg() == 1 && monster[i].getMonsterIsAlive() && monster[i].getMonsterIsAttacking())
        {
            playerLife -= monster[i].getDmgToPlayer();  
            if(playerLife <= 0 && playerDeathTimer == 0)
            {
                playerDeathTimer = 1;
                playerFrameNumber = 0;
                playerFrameTimer = TimeBetween2FramePlayer*2;
                playerFrameMax = PLAYER_FRAME_DEAD;
            }
        }     
    }

    if (playerDeathTimer == 0)
    {
        if (invincibleTimer > 0)
        {
            invincibleTimer --;
        }

        ghostPlayerX = 0;
        ghostPlayerY = 0;
        if (playerIsAttacking)
        {
            if (playerFrameNumber == playerFrameMax-1)
            {
                playerIsAttacking = 0;
                for (int i = 0; i < monsterNumber; i++)
                {
                    if (monster[i].getMonsterIsAlive() == 1)
                        monster[i].setIsGettingDamage(0);
                }
                map.setTileIsGettingDamage(0);
            }
            int dmg = 20*daggerOn + 10*spearOn + 2*(1-daggerOn)*(1-spearOn);
            for (int i = 0; i < monsterNumber; i++)
            {
                if(monster[i].getMonsterIsAlive() == 1 && monster[i].getIsGettingDamage() == 0)
                {
                    if (Collision::PixelPerfectTest(playerSprite, monster[i].getMonsterSprite()))
                    {
                        monster[i].setMonsterLife(monster[i].getMonsterLife() - dmg);
                        monster[i].setIsGettingDamage(1);
                    }
                }
            }
            playerAttackTile(map,dmg);
        }
        else
        {
            if(input.getButton().run)
                playerIsRunning = 5;
            else
                playerIsRunning = 0;
            if (input.getButton().switchDagger == true)
            {
                if (changeDaggerState)
                {
                    if (!daggerOn)
                    {
                        playerSprite.setTexture(daggerTexture);
                        daggerOn = 1;
                        spearOn = 0;
                    }
                    else
                    {
                        playerSprite.setTexture(playerTexture);
                        daggerOn = 0;
                    }
                    changeDaggerState = 0;
                }
            }
            else if (input.getButton().switchSpear == true)
            {
                if (changeSpearState)
                {
                    if(!spearOn)
                    {
                        playerSprite.setTexture(spearTexture);
                        spearOn = 1;
                        daggerOn = 0;
                    }
                    else
                    {
                        playerSprite.setTexture(playerTexture);
                        spearOn = 0;
                    }
                    changeSpearState = 0;
                }
            }
            else if (input.getButton().switchSpear == false && input.getButton().switchDagger == false)
            {
                changeSpearState = 1;
                changeDaggerState = 1;
                
            }
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
            startPlayerState = START_PLAYER_WALK;
            //attack
            if (input.getButton().attack == true)
            {
                playerIsAttacking = 1;
                playerFrameNumber = 0;
                if(daggerOn)
                {
                    startPlayerState = START_PlAYER_ATTACK_DAGGER;
                    playerFrameTimer = TimeBetween2FramePlayer;
                    playerFrameMax = PlAYER_FRAME_ATTACK_DAGGER;
                }
                else if(spearOn)
                {
                    startPlayerState = START_PlAYER_ATTACK_SPEAR;
                    playerFrameTimer = TimeBetween2FramePlayer;
                    playerFrameMax = PlAYER_FRAME_ATTACK_SPEAR;
                }
                else
                {
                    startPlayerState = START_PlAYER_ATTACK_DAGGER;
                    playerFrameTimer = TimeBetween2FramePlayer;
                    playerFrameMax = PlAYER_FRAME_ATTACK_DAGGER;                    
                }
                
            }
            //
            playerMapCollision(map);
            playerMonsterCollision(monster, input, monsterNumber);
            //playerCenterScrolling(map);
        }
    }

    /*if (playerDeathTimer > 0)
    {
        playerDeathTimer --;
        if (playerDeathTimer == 0)
        {
            playerX = 0;
            playerY= 0;
            ghostPlayerX = 0;
            ghostPlayerY = 0;
            playerLife = 100;
        }
    }*/
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
            else if(map.getTileBreak(ny+i,nx+2) == breakMUR1||map.getTileBreak(ny+i,nx+2) == breakMUR2)
            {
                testcol = map.getSpriteBreak(ny+i,nx+2);
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
            else if (map.getTileBreak(ny+i,nx) == breakMUR1 || map.getTileBreak(ny+i,nx) == breakMUR2)
            {
                testcol = map.getSpriteBreak(ny+i,nx);
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
            else if(map.getTileBreak(ny+2,nx+i) == breakMUR1 || map.getTileBreak(ny+2,nx+i) == breakMUR2)
            {
                testcol = map.getSpriteBreak(ny+2,nx+i);
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
            if (map.getTileCollision(ny,nx+i) == MUR1 )
            {
                testcol = map.getSprite(ny,nx+i);
                playerSprite.setPosition(Vector2f(playerX+ghostPlayerX,playerY+ghostPlayerY));
                if(Collision::PixelPerfectTest(playerSprite,testcol))
                {
                    ghostPlayerY = 0;
                    break;
                }
            }
            else if(map.getTileBreak(ny,nx+i) == breakMUR1 || map.getTileBreak(ny,nx+i) == breakMUR2)
            {
                testcol = map.getSpriteBreak(ny,nx+i);
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
        if (monster[i].getMonsterIsAlive())
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

void Player::playerAttackTile(Map &map,int tiledmg)
{
    if(map.getTileIsGettingDamage() == 0)
    {
        Sprite testcol;
        int Wtest = (PLAYERW/Tile_Size)+1;
        int Htest = (PLAYERH/Tile_Size)+1;
        int nx,ny;
        nx = (playerX)/Tile_Size;
        ny = (playerY)/Tile_Size;
        if(playerDirection == playerRIGHT)
        {
            for (int i=0; i < Wtest ; i++)
            {
                if (map.getTileBreak(ny+i,nx+2) == breakMUR1 || map.getTileBreak(ny+i,nx+2) == breakMUR2)
                {
                    testcol = map.getSpriteBreak(ny+i,nx+2);
                    playerSprite.setPosition(Vector2f(playerX,playerY));
                    if(Collision::PixelPerfectTest(playerSprite,testcol))
                    {
                        map.setLifeTileBreak(ny+i,nx+2, map.getLifeTileBreak(ny+i,nx+2)-tiledmg );
                        map.setTileIsGettingDamage(1);
                        break;
                    }
                }
            }
        }
        else if(playerDirection == playerLEFT)
        {
            for (int i=0; i < Wtest ; i++)
            {
                if (map.getTileBreak(ny+i,nx) == breakMUR1|| map.getTileBreak(ny+i,nx) == breakMUR2)
                {
                    testcol = map.getSpriteBreak(ny+i,nx);
                    playerSprite.setPosition(Vector2f(playerX,playerY));
                    if(Collision::PixelPerfectTest(playerSprite,testcol))
                    {
                        map.setLifeTileBreak(ny+i,nx, map.getLifeTileBreak(ny+i,nx)-tiledmg );
                        map.setTileIsGettingDamage(1);
                        break;
                    }
                }
            }
        }
        if(playerDirection == playerDOWN)
        {
            for (int i=0; i < Htest ; i++)
            {
                if (map.getTileBreak(ny+2,nx+i) == breakMUR1 || map.getTileBreak(ny+2,nx+i) == breakMUR2)
                {
                    testcol = map.getSpriteBreak(ny+2,nx+i);
                    playerSprite.setPosition(Vector2f(playerX,playerY));
                    if(Collision::PixelPerfectTest(playerSprite,testcol))
                    {
                        map.setLifeTileBreak(ny+2,nx+i, map.getLifeTileBreak(ny+2,nx+i)-tiledmg );
                        map.setTileIsGettingDamage(1);
                        break;
                    }
                }
            }
        }
        else if(playerDirection == playerUP)
        {
            for (int i=0; i < Htest ; i++)
            {
                if (map.getTileBreak(ny,nx+i) == breakMUR1)
                {
                    testcol = map.getSpriteBreak(ny,nx+i);
                    playerSprite.setPosition(Vector2f(playerX,playerY));
                    if(Collision::PixelPerfectTest(playerSprite,testcol))
                    {
                        map.setLifeTileBreak(ny,nx+i, map.getLifeTileBreak(ny,nx+i)-tiledmg );
                        map.setTileIsGettingDamage(1);
                        break;
                    }
                }
            }
        }
    }
}