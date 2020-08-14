#include "monster.hpp"

using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24
#define Tile_Size 32

#define START_MONSTER_WALK 7
#define MONSTER_FRAME_MAX 7

#define MONSTERH 64
#define MONSTERW 64

Monster::Monster()
{
    if(!monsterTexture.loadFromFile("Images/testMonster.png"))
    {
        std::cout << "Err chargement de l'image du monstre" << std::endl;
    }
    else
    {
        monsterSprite.setTexture(monsterTexture);
    }

    ghostMonsterX = 0;
    ghostMonsterY = 0;
    monsterLife = 100; 
    monsterLifeMax = 100;
    monsterX = 0;
    monsterY = 0;
    monsterFrameNumber = 0;
    monsterFrameTimer = 0;
    monsterFrameMax = 0;
    monsterEtat = 0;
    monsterDirection = 0;
}

int Monster::getMonsterH(void) const { return monsterH; }
int Monster::getMonsterW(void) const { return monsterW; }
int Monster::getMonsterX(void) const { return monsterX; }
int Monster::getMonsterY(void) const { return monsterY; }
int Monster::getGhostMonsterX(void) const { return ghostMonsterX; }
int Monster::getGhostMonsterY(void) const { return ghostMonsterY; }
Sprite Monster::getMonsterSprite(void) const { return monsterSprite; }

void Monster::setMonsterStand(int valeur){ monsterStand = valeur; }

void Monster::drawMonster(RenderWindow &window)
{
    prevMonsterFrameNumber = monsterFrameNumber;
    if (monsterFrameTimer <= 0)
    {
        monsterFrameTimer = TimeBetween2FrameMonster;
        monsterFrameNumber ++;
        if (monsterFrameNumber >= monsterFrameMax)
        {
            monsterFrameNumber = 0;
        }
    }
    else
    {
        if(monsterEtat != IDLE)
        {
            monsterFrameTimer -= 1 + (monsterIsRunning*2);
        }
        else
        {
            //playerFrameTimer --;
        }
    }

    monsterSprite.setPosition(Vector2f(monsterX,monsterY));
    monsterSprite.setTextureRect(IntRect(monsterFrameNumber*monsterW, 
    (monsterDirection+START_MONSTER_WALK)*monsterH,
    monsterW,monsterH));
    window.draw(monsterSprite);    

    RectangleShape monsterLifeBar(Vector2f(MONSTERW,8));//playerLifeBar
    RectangleShape monsterLifeBarInside(Vector2f(MONSTERW*(monsterLife/monsterLifeMax),8));
    monsterLifeBarInside.setFillColor(Color::Red);
    monsterLifeBarInside.setPosition(monsterX,monsterY);
    monsterLifeBar.setFillColor(Color::Transparent);
    monsterLifeBar.setPosition(monsterX,monsterY);
    monsterLifeBar.setOutlineThickness(2);
    monsterLifeBar.setOutlineColor(Color(0,0,0));
    window.draw(monsterLifeBar);
    window.draw(monsterLifeBarInside);
}

void Monster::initMonster(int x, int y)
{
    monsterLife = 100;
    monsterLifeMax = 100;

    monsterDirection = monsterDOWN;
    prevMonsterDirection = monsterDOWN;
    monsterEtat = IDLE;

    monsterFrameNumber = 0;
    prevMonsterFrameNumber = 0;
    monsterFrameTimer = TimeBetween2FrameMonster;
    monsterFrameMax = MONSTER_FRAME_MAX;

    monsterX = x;
    monsterY = y;
    monsterH = MONSTERH;
    monsterW = MONSTERW;

    monsterStand = 1;
    
    monsterIsAttacking = 0;
}

void Monster::monsterMapCollision(Map & map)
{
    int i,x1,x2,y1,y2;

    if(monsterH > Tile_Size)
    {
        i = Tile_Size;
    }
    else
    {
        i = monsterH;
    }
    
    for(;;)
    {
        x1 = (monsterX + ghostMonsterX)/Tile_Size ;
        x2 = (monsterX + ghostMonsterX + monsterW - 1)/Tile_Size ;

        y1 = (monsterY)/Tile_Size ;
        y2 = (monsterY + i - 1)/Tile_Size ;   

        if(x1 >= 0 && x2 < screen_W && y1 >= 0 && y2 < screen_H)
        {
            if(ghostMonsterX > 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x2) == MUR1 || map.getTileCollision(y2,x2) == MUR1)
                {
                    monsterX = x2*Tile_Size;
                    monsterX -= (monsterW+1);
                    ghostMonsterX = 0;
                }
            }
            else if(ghostMonsterX < 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x1) == MUR1 || map.getTileCollision(y2,x1) == MUR1)
                {
                    monsterX = (x1+1)*Tile_Size;
                    ghostMonsterX = 0;
                }
            }            
        }
        
        if(i==monsterH)
        {
            break;
        }
        i += Tile_Size;

        if(i>monsterH)
        {
            i = monsterH;
        }    
    }

    if(monsterW > Tile_Size)
    {
        i = Tile_Size;
    }
    else
    {
        i = monsterW;
    }  
    for(;;)
    {
        x1 = monsterX/Tile_Size ;
        x2 = (monsterX + i)/Tile_Size ;

        y1 = (monsterY + ghostMonsterY)/Tile_Size ;
        y2 = (monsterY + ghostMonsterY + monsterH)/Tile_Size ;   

        if(x1 >= 0 && x2 < screen_W && y1 >= 0 && y2 < screen_H)
        {
            if(ghostMonsterY > 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y2,x1) == MUR1 || map.getTileCollision(y2,x2) == MUR1)
                {
                    monsterY = y2*Tile_Size;
                    monsterY -= (monsterH+1);
                    ghostMonsterY = 0;
                }
            }
            else if(ghostMonsterY < 0)
            {
                //verifier ici si on collision map
                //si ok alors
                if(map.getTileCollision(y1,x1) == MUR1 || map.getTileCollision(y1,x2) == MUR1)
                {
                    monsterY = (y1+1)*Tile_Size;
                    ghostMonsterY = 0;
                }
            }            
        }
        if(i==monsterW)
        {
            break;
        }
        i += Tile_Size;

        if(i>monsterW)
        {
            i = monsterW;
        }    
    }

    prevMonsterX = monsterX;
    prevMonsterY = monsterY;
    monsterX += ghostMonsterX;
    monsterY += ghostMonsterY;

    if(monsterX < 0)
    {
        monsterX = 0;
    }
    else if (monsterX + monsterW > screen_W)
    {
        monsterX = screen_W - monsterW;
    }
    else if(monsterY < 0)
    {
        monsterY = 0;
    }
    else if (monsterY + monsterH > screen_H)
    {
        monsterY = screen_H - monsterH;
    }    
}


void Monster::updateMonster(std::string action, Map &map)
{
    if (monsterStand)
    {
        ghostMonsterX = 0;
        ghostMonsterY = 0;

        if(action == "run")
            monsterIsRunning = 5;
        else
            monsterIsRunning = 0;

        if(action == "left")
        {
            ghostMonsterX -= monsterSpeed + monsterIsRunning;
            prevMonsterDirection = monsterDirection;
            monsterDirection = monsterLEFT;

            if(monsterEtat != monsterWALK)
            {
                monsterEtat = monsterWALK;
                monsterFrameNumber = 0;
                monsterFrameTimer = TimeBetween2FrameMonster;
                monsterFrameMax = MONSTER_FRAME_MAX;
            }
        }
        else if(action == "right")
        {
            ghostMonsterX += monsterSpeed + monsterIsRunning;
            prevMonsterDirection = monsterDirection;
            monsterDirection = monsterRIGHT;

            if(monsterEtat != monsterWALK)
            {
                monsterEtat = monsterWALK;
                monsterFrameNumber = 0;
                monsterFrameTimer = TimeBetween2FrameMonster;
                monsterFrameMax = MONSTER_FRAME_MAX;
            }
        }
        else if(action == "up")
        {
            ghostMonsterY -= monsterSpeed + monsterIsRunning;
            prevMonsterDirection = monsterDirection;
            monsterDirection = monsterUP;

            if(monsterEtat != monsterWALK)
            {
                monsterEtat = monsterWALK;
                monsterFrameNumber = 0;
                monsterFrameTimer = TimeBetween2FrameMonster;
                monsterFrameMax = MONSTER_FRAME_MAX;
            }
        }
        else if(action == "down")
        {
            ghostMonsterY += monsterSpeed + monsterIsRunning;
            prevMonsterDirection = monsterDirection;
            monsterDirection = monsterDOWN;

            if(monsterEtat != monsterWALK)
            {
                monsterEtat = monsterWALK;
                monsterFrameNumber = 0;
                monsterFrameTimer = TimeBetween2FrameMonster;
                monsterFrameMax = MONSTER_FRAME_MAX;
            }
        }         
        else if(action != "down" && action != "up" &&
                action != "left" == false && action != "right")
        {
            if (monsterEtat != IDLE)
            {
                monsterEtat = IDLE;
                monsterFrameNumber = 0;
                monsterFrameTimer = TimeBetween2FrameMonster;
                monsterFrameMax = 3;
            }
        }
        monsterMapCollision(map);
    }
    else
    {
        ghostMonsterX = 0;
        ghostMonsterY = 0;
        if (monsterEtat != IDLE)
        {
            monsterEtat = IDLE;
            monsterFrameNumber = 0;
            monsterFrameTimer = TimeBetween2FrameMonster;
            monsterFrameMax = 3;
        }    
    }
}