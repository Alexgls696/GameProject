#pragma once
#include "Players.h"
#include "../Library.h"
using namespace sf;
using namespace std;
class PlayerPacMan : public Players
{
private:
    float CurrentFrame = 0;
    Clock clock;
    float time;
    float speed = 0.5;
public:
    PlayerPacMan():Players()
    {
        image.loadFromFile("Textures/PacMan.png");
        image.createMaskFromColor(Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 50, 46));
        sprite.setOrigin(sprite.getPosition().x+sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
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
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 3000;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        CurrentFrame += 0.02 * time;
        sprite.setTextureRect(IntRect(55*int(CurrentFrame), 0, 50, 46));
        switch(direction)
        {
        case LEFT:
            sprite.move(-speed * time, 0);
            sprite.setRotation(180);
            break;
        case RIGHT:
            sprite.move(speed * time, 0);
            sprite.setRotation(0);
            break;
        case UP:
            sprite.move(0, -speed * time);
            sprite.setRotation(270);
            break;
        case DOWN:
            sprite.move(0, speed * time);
            sprite.setRotation(90);
            break;
        case STOP:
            break;
        }
    }

    void checkBounds() override
    {
        if(sprite.getPosition().x-texture.getSize().x/2 <0 ||sprite.getPosition().x+texture.getSize().x/2>1920)
        {
            direction=STOP;
            fail=true;
        }
        if(sprite.getPosition().y-texture.getSize().y/2 <0 ||sprite.getPosition().y+texture.getSize().y/2>1080)
        {
            fail=true;
            direction=STOP;
        }
    }
};
