#pragma once
#include "Players.h"

class PlayerCowboy : public  Players
{
private:
    float CurrentFrame = 0;
    Clock clock;
    float time;
    float speed = 0.1;
    bool flag_UP = false, flag_DOWN = false, flag_LEFT = false, flag_RIGHT = false;
public:
    PlayerCowboy()
    {
        direction=STOP;
        texture.loadFromFile("Textures/cowboy.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(10, 0, 60, 80));
        //sprite.setScale(1.5f, 1.5f);
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2);
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

        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        
        if(direction == LEFT && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 15 && !flag_LEFT)
        {
            flag_RIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 0, 60, 80));
            sprite.move(-speed * time, 0);
        }

        if (direction == RIGHT && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH-25 && !flag_RIGHT)
        {
            flag_LEFT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 20, 85, 60, 80));
            sprite.move(speed * time, 0);
        }

        if (direction == UP && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10 && !flag_UP)
        {
            flag_DOWN = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 265, 60, 80));
            sprite.move(0, -speed * time);
        }

        if (direction == DOWN && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT-40 && !flag_DOWN)
        {
            flag_UP = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 175, 60, 80));
            sprite.move(0, speed * time);
        }
    }

    void draw(RenderWindow& window)
    {
        window.draw(sprite);
    }
    void Direction(Event& event)
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

    void checkBounds() override
    {
        if (sprite.getPosition().x-sprite.getTextureRect().width/2 <0 ||sprite.getPosition().x+sprite.getTextureRect().width/2>1920)
        {
            direction=STOP;
        }
        if (sprite.getPosition().y-sprite.getTextureRect().height/2 <0 ||sprite.getPosition().y+sprite.getTextureRect().height/2>1080)
        {
            direction=STOP;
        }
    }
};