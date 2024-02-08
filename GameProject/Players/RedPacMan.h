#pragma once
#pragma once
#include "Players.h"
#include "../Library.h"

using namespace sf;
using namespace std;

class PlayerRedPacMan : public Players
{
public:
    PlayerRedPacMan():Players()
    {
        image.loadFromFile("Textures/red.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    void draw(RenderWindow&window) override
    {
        window.draw(sprite);
    }
    
    void Direction(Event&event) override {
        if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction = LEFT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction = UP;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = RIGHT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction = DOWN;
        }
    }
    void move() override
    {
        switch(direction)
        {
        case LEFT:
            sprite.move(Vector2f(-5,0)); break;
        case RIGHT:
            sprite.move(Vector2f(5,0)); break;
        case UP:
            sprite.move(Vector2f(0,-5)); break;
        case DOWN:
            sprite.move(Vector2f(0,5)); break;
        case STOP:
            break;
        }
        
    }
};
