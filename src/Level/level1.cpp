#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "level1.hpp"

#define screen_W 1024
#define screen_H 768

using namespace sf;

std::vector<std::string> action = {"down","right","up","left","attack"};
int i,j,k,m,n = 0;
int rand_action;

void level1::setForm()
{

}

void level1::setCaracter()
{
	player.initPlayer();
}

void level1::setMonster()
{
	monster[0].initMonster(224,288);
	monster[1].initMonster(512,224);
	monster[2].initMonster(288,32);
	monster[3].initMonster(32,288);
	monster[4].initMonster(64,512);
}

void level1::setTexture()
{
	std::string filename;
	filename = "Map/map1.txt";
	map.changeLevel(filename);
}

void level1::draw()
{
	window->clear();
	map.drawMap(1,*window);
	map.drawMap(2,*window);
	map.drawMap(3,*window);
	map.drawMap(4,*window);
	player.drawPlayer(*window);
	monster[0].drawMonster(*window);
	monster[1].drawMonster(*window);
	monster[2].drawMonster(*window);
	monster[3].drawMonster(*window);
	monster[4].drawMonster(*window);
	//window->draw(cercle);
	//window->draw(rectangle);
	window->draw(sprite_perso);
}

void level1::run_event(Input &input)
{
	int monsterNumber = 5;
	input.gestionInputs(*window);
	player.updatePlayer(input, map,monster,monsterNumber);
	monster[0].updateMonster("nul",map,monster,monsterNumber,0,player.getPlayerSprite());
	if (i==0)
	{
		monster[1].updateMonster("right",map,monster,monsterNumber,1,player.getPlayerSprite());
		if(monster[1].getMonsterX() > 768)
		{
			i = 1;
		}
	}
	else
	{
		monster[1].updateMonster("left",map,monster,monsterNumber,1,player.getPlayerSprite());
		if(monster[1].getMonsterX() < 512)
		{
			i = 0;
		}		
	}
	if (j==0)
	{
		monster[2].updateMonster("down",map,monster,monsterNumber,2,player.getPlayerSprite());
		if(monster[2].getMonsterY() > 256)
		{
			j = 1;
		}
	}
	else
	{
		monster[2].updateMonster("up",map,monster,monsterNumber,2,player.getPlayerSprite());
		if(monster[2].getMonsterY() < 32)
		{
			j = 0;
		}		
	}
	monster[3].updateMonster("right",map,monster,monsterNumber,3,player.getPlayerSprite());	

	if (k == 0)
	{
		monster[4].updateMonster("attack",map,monster,monsterNumber,4,player.getPlayerSprite());
		k++;
	}
	else if (k==60)
	{
		monster[4].updateMonster("nul",map,monster,monsterNumber,4,player.getPlayerSprite());
		k=0;
	}
	else
	{
		monster[4].updateMonster("nul",map,monster,monsterNumber,4,player.getPlayerSprite());
		k++;
	}
}