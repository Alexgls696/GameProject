﻿#pragma once
#include "Players.h"

class PlayerCowboy : public  Players
{
private:
    float CurrentFrame = 0;
    Clock clock;
    float time;
    float speed = 0.1;
    bool flag_UP = false, flag_DOWN = false, flag_LEFT = false, flag_RIGHT = false, flag_DOWNLEFT=false, flag_DOWNRIGHT=false, flag_UPLEFT=false, flag_UPRIGHT=false;
public:
    PlayerCowboy()
    {
        direction=STOP;
        texture.loadFromFile("Textures/cowboy.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(10, 0, 60, 80));
        //sprite.setScale(1.5f, 1.5f);
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getPosition().y+sprite.getTextureRect().height/2); //изм
    }

    void move() override
    {
        if(obstacle && !flag_UP && !flag_DOWN && !flag_LEFT && !flag_RIGHT && !flag_DOWNLEFT && !flag_DOWNRIGHT && !flag_UPLEFT && !flag_UPRIGHT)
        {
            if (direction == UP) flag_UP = true;
            if (direction == DOWN) flag_DOWN = true;
            if (direction == LEFT) flag_LEFT = true;
            if (direction == RIGHT) flag_RIGHT = true;
            if (direction == DOWN_LEFT) flag_DOWNLEFT = true;
            if (direction == DOWN_RIGHT) flag_DOWNRIGHT = true;
            if (direction == UP_LEFT) flag_UPLEFT = true;
            if (direction == UP_RIGHT) flag_UPRIGHT = true;
        }

        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        
        if(direction == LEFT && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 15 && !flag_LEFT)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT =false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 0, 60, 80));
            sprite.move(-speed * time, 0);
        }

        if (direction == RIGHT && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH-25 && !flag_RIGHT)
        {
           flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 20, 85, 60, 80));
            sprite.move(speed * time, 0);
        }

        if (direction == UP && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10 && !flag_UP)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 265, 60, 80));
            sprite.move(0, -speed * time);
        }

        if (direction == DOWN && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT-40 && !flag_DOWN)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 175, 60, 80));
            sprite.move(0, speed * time);
        }

        if (direction == DOWN_LEFT && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT - 40 && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 15 && !flag_DOWNLEFT)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 355, 60, 80));
            sprite.move(-speed * time, speed * time);
        }

        if (direction == DOWN_RIGHT && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT - 40 && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH - 25 && !flag_DOWNRIGHT)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 445, 60, 80));
            sprite.move(speed * time, speed * time);
        }

        if (direction == UP_LEFT && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10 && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 15 && !flag_UPLEFT)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 5, 535, 60, 78));
            sprite.move(-speed * time, -speed * time);
        }

        if (direction == UP_RIGHT && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10 && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH - 25 && !flag_UPRIGHT)
        {
            flag_UP = false;
            flag_DOWN = false;
            flag_LEFT = false;
            flag_RIGHT = false;
            flag_DOWNLEFT = false;
            flag_DOWNRIGHT = false;
            flag_UPLEFT = false;
            flag_UPRIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 620, 60, 80));
            sprite.move(speed * time, -speed * time);
        }
    }

    void draw(RenderWindow& window)
    {
        window.draw(sprite);
    }
    void Direction(Event& event)
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)
            && !(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            && !(Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)))
        {
            direction = UP;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left)
            && !(Keyboard::isKeyPressed(sf::Keyboard::S))
            && !((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))))
        {
            direction = LEFT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right)
            && !(Keyboard::isKeyPressed(sf::Keyboard::S))
            && !((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))))
        {
            direction = RIGHT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down)
            && !(Keyboard::isKeyPressed(sf::Keyboard::D))
            && !(Keyboard::isKeyPressed(sf::Keyboard::Right))
            && !(Keyboard::isKeyPressed(sf::Keyboard::A))
            && !(Keyboard::isKeyPressed(sf::Keyboard::Left)))
        {
            direction = DOWN;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Left)))
            || (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::A))))
        {
            direction = DOWN_LEFT;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Right)))
            || (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::D))))
        {
            direction = DOWN_RIGHT;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left) ||
            Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
        {
            direction = UP_LEFT;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) && (Keyboard::isKeyPressed(Keyboard::Right))) ||
            (Keyboard::isKeyPressed(Keyboard::W) && (Keyboard::isKeyPressed(Keyboard::D))))
        {
            direction = UP_RIGHT;
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
