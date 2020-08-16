#ifndef MAP_H
#define MAP_H

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

class Map
{
    public:
        Map(std::string const filename);

        void loadMap();
        void drawMap(int layer, RenderWindow &window);
        void changeLevel(std::string filename);
        void saveMap() const;
        void changeTile(int layer, std::pair<int,int> coord, int tile);

        int getTileCollision(int x,int y) const;
        Sprite getSprite(int x, int y) const;
        Sprite getSpriteBreak(int x, int y) const;

        int getTileBreak(int x,int y) const;
        int getLifeTileBreak(int x,int y) const;
        int getTileIsGettingDamage(void) const;

        void setTileBreak(int x,int y, int valeur);
        void setLifeTileBreak(int x,int y, int valeur);
        void setTileIsGettingDamage(int valeur);

    protected:
        int tile1[nbTile_H][nbTile_W];
        int tile2[nbTile_H][nbTile_W];
        int tile3[nbTile_H][nbTile_W];
        int tile4[nbTile_H][nbTile_W];
        int lifeTile4[nbTile_H][nbTile_W];

        std::string mapFilename ;
        std::string tilesFilename[2];

        int tileIsGettingDamage;

        Texture tileSetTexture1;
        Sprite tileSet1;
        Texture tileSetTexture2;
        Sprite tileSet2;

        int mapTimerChangeTile;
        int currentTileNumber;

        const int TimeBetween2Tile = 20;

};
#endif
