#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "map.hpp"
using namespace sf;

#define screen_W 1024
#define screen_H 768
#define nbTile_W 32
#define nbTile_H 24
#define Tile_Size 32

Map::Map()
{
    if(!tileSetTexture1.loadFromFile("Images/tileset1.png"))
    {
        std::cout << "Err chargement de l'image du tilset 1" << std::endl;
    }
    else
    {
        tileSet1.setTexture(tileSetTexture1);
    }
    if(!tileSetTexture2.loadFromFile("Images/tileset2.png"))
    {
        std::cout << "Err chargement de l'image du tilset 2" << std::endl;
    }
    else
    {
        tileSet2.setTexture(tileSetTexture2);
    } 

    currentTileNumber = 0;
    mapTimerChangeTile = TimeBetween2Tile * 3;
}


int Map::getTileCollision(int x,int y) const { return tile3[x][y]; }
int Map::getTileBreak(int x,int y) const { return tile4[x][y]; }
int Map::getLifeTileBreak(int x,int y) const { return lifeTile4[x][y]; }

void Map::setTileBreak(int x,int y, int valeur) { tile4[x][y] = valeur; }
void Map::setLifeTileBreak(int x,int y, int valeur)
{ 
    lifeTile4[x][y] = valeur; 
    if (lifeTile4[x][y] == 50)
    {
        tile4[x][y] = 288;
    }
    if (lifeTile4[x][y] == 0)
    {
        tile4[x][y] = 0;
    }
}

void Map::loadMap(std::string filename)
{
    std::fstream fin;
    int x = 0;
    int y = 0; 

    std::vector<std::vector<int>> lignes;
    std::vector<int> ligne_data;

    std::stringstream iostr;

    std::string strBuf,strTmp;

    fin.open(filename,std::fstream::in);
    if(!fin.is_open())
    {
        std::cout << "Erreur chargement du fichier " << filename << std::endl;
    }

    std::cout << "Remplissage vecteur Map" << std::endl;
    while(!fin.eof())
    {
        getline(fin,strBuf);
        if(!strBuf.size())
        {
            continue;
        }
        iostr.clear();
        iostr.str(strBuf);
        ligne_data.clear();

        while(true)
        {
            getline(iostr,strTmp,',');
            ligne_data.push_back(atoi(strTmp.c_str()));
            if(!iostr.good()) break;
        }
        if(ligne_data.size())
            lignes.push_back(ligne_data);
    }
    fin.close();

    std::cout << "Remplissage tile1" << std::endl;
    for (x=0; x < nbTile_H; x++)
    {
        for (y=0; y < nbTile_W; y++)
        {
            tile1[x][y] = lignes[x][y];
        }
    }
    std::cout << "Remplissage tile2" << std::endl;
    for (x=0; x < nbTile_H; x++)
    {
        for (y=0; y < nbTile_W; y++)
        {
            tile2[x][y] = lignes[x+nbTile_H][y];
        }
    }
    std::cout << "Remplissage tile3" << std::endl;
    for (x=0; x < nbTile_H; x++)
    {
        for (y=0; y < nbTile_W; y++)
        {
            tile3[x][y] = lignes[x+nbTile_H*2][y];
        }
    }
    std::cout << "Remplissage tile4" << std::endl;
    for (x=0; x < nbTile_H; x++)
    {
        for (y=0; y < nbTile_W; y++)
        {
            tile4[x][y] = lignes[x+nbTile_H*3][y];
        }
    }
    std::cout << "Remplissage lifeTile4" << std::endl;
    for (x=0; x < nbTile_H; x++)
    {
        for (y=0; y < nbTile_W; y++)
        {
            lifeTile4[x][y] = lignes[x+nbTile_H*4][y];
        }
    }
    std::cout << "end loadmap " << std::endl;
}

void Map::drawMap(int layer, RenderWindow &window)
{
    int x,y,a,posx,posy; 

    if (mapTimerChangeTile <= 0)
    {
        if (currentTileNumber == 0)
        {
            currentTileNumber = 1;
            mapTimerChangeTile = TimeBetween2Tile * 3;
        }
        else
        {
            currentTileNumber = 0;
            mapTimerChangeTile = TimeBetween2Tile * 3;
        }
    }
    else
    {
        mapTimerChangeTile --;
    }

    if (layer==1)
    {
        for (x=0; x < nbTile_H; x++)
        {
            for (y=0; y < nbTile_W; y++)
            {
                a = tile1[x][y];
                posx = a % 10 * Tile_Size;
                posy = a / 10 * Tile_Size;
                
                if (currentTileNumber == 0)
                {
                    tileSet1.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet1.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet1);
                }
                else
                {
                    tileSet2.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet2.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet2);                    
                }

            }
        }
    }
    else if (layer == 2)
    {
        for (x=0; x < nbTile_H; x++)
        {
            for (y=0; y < nbTile_W; y++)
            {
                a = tile2[x][y];
                posx = a % 10 * Tile_Size;
                posy = a / 10 * Tile_Size;

                if (currentTileNumber == 0)
                {
                    tileSet1.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet1.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet1);
                }
                else
                {
                    tileSet2.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet2.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet2);                    
                }
            }
        }     
    }
    else if (layer == 3)
    {
        for (x=0; x < nbTile_H; x++)
        {
            for (y=0; y < nbTile_W; y++)
            {
                a = tile3[x][y];
                posx = a % 10 * Tile_Size;
                posy = a / 10 * Tile_Size;

                if (currentTileNumber == 0)
                {
                    tileSet1.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet1.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet1);
                }
                else
                {
                    tileSet2.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet2.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet2);                    
                }
            }
        }    
    }
    else if (layer == 4)
    {
        for (x=0; x < nbTile_H; x++)
        {
            for (y=0; y < nbTile_W; y++)
            {
                a = tile4[x][y];
                posx = a % 10 * Tile_Size;
                posy = a / 10 * Tile_Size;

                if (currentTileNumber == 0)
                {
                    tileSet1.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet1.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet1);
                }
                else
                {
                    tileSet2.setPosition(Vector2f(y*Tile_Size,x*Tile_Size));
                    tileSet2.setTextureRect(IntRect(posx,posy,Tile_Size,Tile_Size));
                    window.draw(tileSet2);                    
                }
            }
        }    
    }
}


void Map::changeLevel(std::string filename)
{
    loadMap(filename);
}