#pragma once
#include "Players.h"
#include "../Library.h"
using namespace sf;
using namespace std;
class PlayerPacMan : public Players
{
private:
    int StartAngle = 0;
public:
    PlayerPacMan():Players()
    {
        image.loadFromFile("Textures/one1.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getPosition().x+texture.getSize().x/2,sprite.getPosition().y+texture.getSize().y/2);
    }
    
    void draw(RenderWindow&window) override
    {
        window.draw(sprite);
    }
    
    void Direction(Event&event) override
    {
        if(!pressed)
        {
            if (Keyboard::isKeyPressed(sf::Keyboard::A)&&direction!=LEFT) {
                pressed=true;
                direction = LEFT;
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::W)&&direction!=UP) {
                pressed=true;
                direction = UP;
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::D)&&direction!=RIGHT) {
                pressed=true;
                direction = RIGHT;
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::S)&&direction!=DOWN) {
                pressed=true;
                direction = DOWN;
            }
        }
        if(event.type==Event::KeyReleased)
        {
            pressed=false;
        }
    }
    
    void move() override
    {
        switch(direction)
        {
        case LEFT:
            sprite.move(Vector2f(-5,0));
            sprite.setRotation(180);
            break;
        case RIGHT:
            sprite.move(Vector2f(5,0));
            sprite.setRotation(0);
            break;
        case UP:
            sprite.move(Vector2f(0,-5));
            sprite.setRotation(270);
            break;
        case DOWN:
            sprite.move(Vector2f(0,5));
            sprite.setRotation(90);
            break;
        case STOP:
            break;
        }
    }
};
