#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

Vector2i posSouris;

RenderWindow window;
CircleShape cercle;
RectangleShape rectangle;
CircleShape octogone(30,8);
ConvexShape convex(5);

Texture perso;
Sprite sprite_perso;


//vue
View view;

enum Dir {Down,Left,Right,Up};

Vector2i anim(1,Down);
bool updateFPS = true; //vitesse perso anim

void gestion_clavier(){
		if(Keyboard::isKeyPressed(Keyboard::Up)){
			anim.y = Up;
			sprite_perso.move(0,-5);
		}
		else if(Keyboard::isKeyPressed(Keyboard::Down)){
			anim.y = Down;
			sprite_perso.move(0,5);
		}
		else if(Keyboard::isKeyPressed(Keyboard::Left)){
			anim.y = Left;
			sprite_perso.move(-5,0);
		}
		else if(Keyboard::isKeyPressed(Keyboard::Right)){
			anim.y = Right;
			sprite_perso.move(5,0);
		}
		if(sprite_perso.getPosition().x <= 0)
			sprite_perso.setPosition(Vector2f(0,sprite_perso.getPosition().y));
		if(sprite_perso.getPosition().y <= 0)
			sprite_perso.setPosition(Vector2f(sprite_perso.getPosition().x,0));
}

int main(){
	
	window.create(VideoMode(800,600),"SFML works");
	window.setFramerateLimit(60);
	
	cercle.setFillColor(Color(250,250,0));
	cercle.setRadius(50);
	cercle.setPosition(700,400);
	
	rectangle.setFillColor(Color(250,250,0));
	rectangle.setSize(Vector2f(50,100));
	rectangle.setPosition(120,230);
	//srectangle.setRotation(30);
	
	cercle.setOutlineColor(Color(0,250,250));
	cercle.setOutlineThickness(10);
	//shape.setFillColor(Color::Green);
	
	octogone.setFillColor(Color(0,250,0));
	octogone.setPosition(550,50);
	
	Clock time; //gerer anim perso
	
	if(!perso.loadFromFile("Images/boss.png")){
			std::cout<< "Err chargement boss.png" << std::endl;
	}
	perso.setSmooth(true); //lisser la texture::gourmant
	
	Texture backgroundTexture;
	Sprite background;
	
	if(!backgroundTexture.loadFromFile("Images/back1.png")){
			std::cout<< "Err chargement boss.png" << std::endl;
	}
	background.setTexture(backgroundTexture);
	
	
	sprite_perso.setTexture(perso);
	while(window.isOpen()){
	    Event event;
	    while (window.pollEvent(event)){
	        if(event.type == Event::Closed)
	            window.close();
	        if(event.type == Event::KeyPressed)
				updateFPS = true;
			else
				updateFPS = false;
	    }
	    
	    Vector2f lpos(400,300);
	    lpos.x = sprite_perso.getPosition().x;
	    lpos.y = sprite_perso.getPosition().y;
	    
	    gestion_clavier();
	    
	    if(updateFPS == true){
			if(time.getElapsedTime().asMilliseconds() >= 200){
				anim.x --;
				if(anim.x * 32 >= perso.getSize().x)
					anim.x = 2;
					time.restart();
			}
		}
		sprite_perso.setTextureRect(IntRect(anim.x *32, anim.y * 32,32,32)); //( , , largeur,hauteur)
	    
	    /*if(Mouse::isButtonPressed(Mouse::Left)){
				posSouris = Mouse::getPosition(window);
				cercle.setPosition(posSouris.x,posSouris.y);
			
		}*/
	    
	    //collision
	    
	    if(sprite_perso.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
		{
			std::cout << " dddd " << std::endl;
			sprite_perso.setPosition(Vector2f(lpos.x,lpos.y));
		}
		
	    
	    
	    //vue
	    view.reset(FloatRect(0,0,800,600));
	    Vector2f position(400,300);
	    position.x = sprite_perso.getPosition().x + 16 - 400;
	    position.y = sprite_perso.getPosition().y + 16 - 300;
	    std::cout << position.x << " " << position.y << std::endl;
	    if(position.x < 0)
			position.x = 0;
		if(position.y < 0)
			position.y = 0;
	    view.reset(FloatRect(position.x,position.y,800,600));
	    window.setView(view);
	    
	    window.draw(background);
	    window.draw(cercle);
	    window.draw(rectangle);
		window.draw(octogone);
		window.draw(sprite_perso);
	    window.display();
	    window.clear();
	}
	return 0;
}