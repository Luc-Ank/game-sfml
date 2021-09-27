#include "spell.hpp"

using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24
#define Tile_Size 32
#define spell_W 32
#define spell_H 32
#define spell_Speed 10

void Spell::initSpell()
{
    if(!spellTexture1.loadFromFile("Images/testSpell.png"))
    {
        std::cout << "Err chargement de l'image du spell" << std::endl;
    }
    else
    {
        spellSprite1.setTexture(spellTexture1);
    }
    for (int i=0;i<maxNumberOfSpell;i++)
    {
        for (int j=0;j<4;j++)
        {
            spellList[i][j] = 0;
        }
    }
    numberOfSpell = 0;
    std::cout << "Spell set end " << std::endl;
}

void Spell::addSpell(int playerX, int playerY, int playerDirection)
{
    if (numberOfSpell < maxNumberOfSpell)
    {
        for(int i = 0; i < maxNumberOfSpell; i++)
        {
            if(spellList[i][3] == 0)
            {
                spellList[i][0] = playerX+16;
                spellList[i][1] = playerY+16;
                spellList[i][2] = playerDirection;
                spellList[i][3] = 1;
                spellSprite[i].setTexture(spellTexture1);
                numberOfSpell += 1;
                break;
            }
        }
    }
    
}

void Spell::updateSpell()
{
    for (int i=0; i<maxNumberOfSpell; i++)
    {
        if (spellList[i][0] < 0 || spellList[i][1] < 0 || 
            spellList[i][0] > screen_W || spellList[i][1] > screen_H)
        {
            spellList[i][3] = 0;
            numberOfSpell --;
        }
        if (spellList[i][3] == 1)
        {
            if (spellList[i][2] == playerLEFT)
            {
                spellList[i][0] += -spell_Speed;
            }
            else if (spellList[i][2] == playerRIGHT)
            {
                spellList[i][0] += spell_Speed;
            }
            else if (spellList[i][2] == playerUP)
            {
                spellList[i][1] += -spell_Speed;
            }
            else if (spellList[i][2] == playerDOWN)
            {
                spellList[i][1] += spell_Speed;
            }
            spellSprite[i].setPosition(Vector2f(spellList[i][0],spellList[i][1]));
        }
    }
}

void Spell::drawSpell(RenderWindow &window)
{   
    for (int i=0; i< maxNumberOfSpell; i++)
    {
        if (spellList[i][3] == 1)
        {
            spellSprite[i].setTextureRect(IntRect(0, 32, spell_W, spell_H));
            window.draw(spellSprite[i]);
        }
    }  
}

void Spell::spellMonsterCollision(Monster monster[], int monsterNumber)
{
    for (int j = 0; j < maxNumberOfSpell; j++)
    {
        for (int i = 0; i < monsterNumber; i++)
        {
            if(monster[i].getMonsterIsAlive() == 1 )//&& monster[i].getIsGettingDamage() == 0)
            {
                if (Collision::PixelPerfectTest(spellSprite[j], monster[i].getMonsterSprite()))
                {
                    monster[i].setMonsterLife(monster[i].getMonsterLife() - 3);
                    //monster[i].setIsGettingDamage(1);
                }
            }
        }
    }    
}