#pragma once
#include "Players.h"

class PlayerCowboy : public  Players
{
private:
    Clock clock;
    float time;
    float speed = 0.1;
    bool flag_UP = false, flag_DOWN = false, flag_LEFT = false, flag_RIGHT = false;
    time_t fireTimer;
    enum Direction lastDirection;
public:
    PlayerCowboy()
    {
        fireTimer = std::clock();
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
        if(direction!=STOP)
        {
            lastDirection=direction;
            flag_enemy_animation = true;
        }
        
        
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        
        if(direction == LEFT && sprite.getPosition().x - sprite.getTextureRect().width / 2 > 10 && !flag_LEFT && !flag_bullet_animation)
        {
            flag_RIGHT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 0, 60, 80));
            sprite.move(-speed * time, 0);
        }

        if (direction == RIGHT && sprite.getPosition().x + sprite.getTextureRect().width / 2 < WIDTH-15 && !flag_RIGHT && !flag_bullet_animation)
        {
            flag_LEFT = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 20, 85, 60, 80));
            sprite.move(speed * time, 0);
        }

        if (direction == UP && sprite.getPosition().y - sprite.getTextureRect().height / 2 > 10 && !flag_UP && !flag_bullet_animation)
        {
            flag_DOWN = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 265, 60, 80));
            sprite.move(0, -speed * time);
        }

        if (direction == DOWN && sprite.getPosition().y + sprite.getTextureRect().height / 2 < HEIGHT-15 && !flag_DOWN && !flag_bullet_animation)
        {
            flag_UP = false;
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 175, 60, 80));
            sprite.move(0, speed * time);
        }

        if(flag_bullet_animation==true && lastDirection==LEFT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 18)
            {
                CurrentFrame = 0;
                flag_bullet_animation=false;
            }
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 540, 60, 80));
        }

        if(flag_bullet_animation==true && lastDirection==RIGHT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 18)
            {
                CurrentFrame = 0;
                flag_bullet_animation=false;
            }
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 630, 65, 80));
        }

        if(flag_bullet_animation==true && lastDirection==DOWN)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 18)
            {
                CurrentFrame =0;
                flag_bullet_animation=false;
            }
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 350, 60, 80));
        }

        if(flag_bullet_animation==true && lastDirection==UP)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 18)
            {
                CurrentFrame =0;
                flag_bullet_animation=false;
            }
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 440, 60, 80));
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
        
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            if(std::clock()-fireTimer>500)
            {
                fireTimer=std::clock(); 
                flag_bullet=true;
                flag_bullet_animation=true;
            }
        }
        if (event.type == Event::KeyReleased)
        {
            direction = STOP;
        }
    }

    enum Direction getDirection() override
    {
        return lastDirection;
    }
};