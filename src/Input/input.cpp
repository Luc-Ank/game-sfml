#include "input.hpp"


using namespace sf;

Input::Input()
{
    button.left = button.right = button.up = button.down = button.run = button.attack = false;
    button.enter = button.protect = button.switchDagger = button.switchSpear = false;
}

Input::Button Input::getButton(void) const {return button;}

void Input::setButton(int bouton, bool etat)
{
    switch(bouton)
    {
        case up:
            button.up = etat;
            break;
        case down:
            button.down = etat;
            break;
        case right:
            button.right = etat;
            break;
        case left:
            button.left = etat;
            break;
        case attack:
            button.attack = etat;
            break;
        case run:
            button.run = etat;
            break;
        case enter:
            button.enter = etat;
            break;
        case protect:
            button.protect = etat;
            break;
        case switchDagger:
            button.switchDagger = etat;
            break;
        case switchSpear:
            button.switchSpear = etat;
            break;
    }
}

void Input::gestionInputs(RenderWindow &window)
{
    getInput(window);
}

void Input::getInput(RenderWindow &window)
{
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                switch(event.key.code)
                {
                    case Keyboard::X:
                        button.run = true;
                        break;
                    case Keyboard::C:
                        button.protect = true;
                        break;
                    case Keyboard::V:
                        button.attack = true;
                        break;
                    case Keyboard::Left:
                        button.left = true;
                        break; 
                    case Keyboard::Right:
                        button.right = true;
                        break;             
                    case Keyboard::Up:
                        button.up = true;
                        break;          
                    case Keyboard::Down:
                        button.down = true;
                        break; 
                    case Keyboard::Return:
                        button.enter = true;
                        break; 
                    case Keyboard::G:
                        button.switchSpear = true;
                        break; 
                    case Keyboard::H:
                        button.switchDagger = true;
                        break;
                    default:
                        break;
                }
                break; 
            case Event::KeyReleased:
                switch (event.key.code)
                {
                    case Keyboard::X:
                        button.run = false;
                        break;
                    case Keyboard::C:
                        button.protect = false;
                        break;
                    case Keyboard::V:
                        button.attack = false;
                        break;
                    case Keyboard::Left:
                        button.left = false;
                        break; 
                    case Keyboard::Right:
                        button.right = false;
                        break;             
                    case Keyboard::Up:
                        button.up = false;
                        break;          
                    case Keyboard::Down:
                        button.down = false;
                        break; 
                    case Keyboard::Return:
                        button.enter = false;
                        break; 
                    case Keyboard::G:
                        button.switchSpear = false;
                        break; 
                    case Keyboard::H:
                        button.switchDagger = false;
                        break;
                    default:
                        break;  
                }
                break; 
            default:
                break;  
        }
    }
}