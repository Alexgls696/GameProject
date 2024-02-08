#pragma once
#include "../Library.h"
using namespace std;
using namespace sf;
class Players
{
protected:
    enum Direction {
        LEFT,RIGHT,UP,DOWN
    };
    Direction direction;
    Texture texture;
    Sprite sprite;
    RectangleShape rectangle_shape;
    Image image;
    Vector2f position;
public:
    virtual void draw(RenderWindow& window) = 0;
    virtual void move() = 0;
    virtual void Direction(Event&event) = 0;
    virtual Sprite&getSprite() {
        return sprite;
    }
};
