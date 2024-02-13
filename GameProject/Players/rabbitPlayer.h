#include "Players.h"
#include "../Library.h"
#ifndef AAA_HEADER
#define AAA_HEADER
class rabbitPlayer : public Players{
private:
    Texture rabbitdTexture, rabbituTexture, rabbitrTexture, rabbitlTexture;
    float speed = 2.5;
    Map*map=nullptr;
    bool flagUp=true,FlagDown=true,flagleft=true,flagRight=true;
    bool flag_UP = false, flag_DOWN = false, flag_LEFT = false, flag_RIGHT = false;
public:
    rabbitPlayer(Map*map) {
        this->map=map;
        direction=STOP;
        rabbituTexture.loadFromFile("Textures/rabbitu.png");
        rabbitdTexture.loadFromFile("Textures/rabbitd.png");
        rabbitrTexture.loadFromFile("Textures/rabbitr.png");
        rabbitlTexture.loadFromFile("Textures/rabbitl.png");
        sprite.setTexture(rabbitrTexture);
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2);
    }
    void draw(RenderWindow& window) override
    {
       window.draw(sprite);
    }
    void move() override
    {
        if(obstacle && !flag_UP && !flag_DOWN && !flag_LEFT && !flag_RIGHT)
        {
            if (direction == UP) flag_UP = true;
            if (direction == DOWN) flag_DOWN = true;
            if (direction == LEFT) flag_LEFT = true;
            if (direction == RIGHT) flag_RIGHT = true;
        }
        if (!obstacle)
        {
            if (direction == UP) flag_UP = false;
            if (direction == DOWN) flag_DOWN = false;
            if (direction == LEFT) flag_LEFT = false;
            if (direction == RIGHT) flag_RIGHT = false;
        }

            if((direction == LEFT && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 10)&& !flag_LEFT)
            {
                flag_RIGHT = false;
                sprite.setTexture(rabbitlTexture);
                sprite.move(-speed, 0);
            }

            if ((direction == RIGHT && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH-15 )&& !flag_RIGHT)
            {
                flag_LEFT = false;
                sprite.setTexture(rabbitrTexture);
                sprite.move(speed, 0);
            }

            if ((direction == UP && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10)&& !flag_UP)
            {
                flag_DOWN = false;
                sprite.setTexture(rabbituTexture);
                sprite.move(0, -speed);
            }

            if ((direction == DOWN && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT-15)&& !flag_DOWN)
            {
                flag_UP = false;
                sprite.setTexture(rabbitdTexture);
                sprite.move(0, speed);
            }
    }
    void Direction(Event& event) override
    {
        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
        {
            direction = UP;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction = LEFT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction = RIGHT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            direction = DOWN;
        }
        if (event.type == Event::KeyReleased)
        {
            direction = STOP;
        }
    }
};
#endif