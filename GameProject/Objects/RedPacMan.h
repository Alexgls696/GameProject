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
    void move(Event&event) override {
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
        switch (direction) {
        case LEFT:
            sprite.move(-1, 0); break;
        case UP:
            sprite.move(0, -1); break;
        case RIGHT:
            sprite.move(1, 0); break;
        case DOWN:
            sprite.move(0, 1); break;
        }
    }
};
