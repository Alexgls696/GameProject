#pragma once
#include "Players.h"

class PlayerCowboy : public  Players
{
private:
    float CurrentFrame = 0;
    Clock clock;
    float time;
    float speed = 0.1;
public:
    PlayerCowboy()
    {
        texture.loadFromFile("Textures/cowboy.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(10, 0, 60, 80));
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
        sprite.setScale(1.5f, 1.5f);
    }

    void move() override
    {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        if (direction == LEFT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 0, 60, 80));
            sprite.move(-speed * time, 0);
        }

        if (direction == RIGHT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 20, 85, 60, 80));
            sprite.move(speed * time, 0);
        }

        if (direction == UP)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 265, 60, 80));
            sprite.move(0, -speed * time);
        }

        if (direction == DOWN)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 175, 60, 80));
            sprite.move(0, speed * time);
        }

        if (direction == DOWN_LEFT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 355, 60, 80));
            sprite.move(-speed * time, speed * time);
        }

        if (direction == DOWN_RIGHT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 10, 445, 60, 80));
            sprite.move(speed * time, speed * time);
        }

        if (direction == UP_LEFT)
        {
            CurrentFrame += 0.01 * time;
            if (CurrentFrame > 16) CurrentFrame -= 16;
            sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + 5, 535, 60, 78));
            sprite.move(-speed * time, -speed * time);
        }

        if (direction == UP_RIGHT)
        {
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
            pressed = true;
            direction = UP;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left)
            && !(Keyboard::isKeyPressed(sf::Keyboard::S))
            && !((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))))
        {
            pressed = true;
            direction = LEFT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Right)
            && !(Keyboard::isKeyPressed(sf::Keyboard::S))
            && !((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))))
        {
            pressed = true;
            direction = RIGHT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down)
            && !(Keyboard::isKeyPressed(sf::Keyboard::D))
            && !(Keyboard::isKeyPressed(sf::Keyboard::Right))
            && !(Keyboard::isKeyPressed(sf::Keyboard::A))
            && !(Keyboard::isKeyPressed(sf::Keyboard::Left)))
        {
            pressed = true;
            direction = DOWN;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Left)))
            || (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::A))))
        {
            pressed = true;
            direction = DOWN_LEFT;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) && (Keyboard::isKeyPressed(Keyboard::Right)))
            || (Keyboard::isKeyPressed(Keyboard::S) && (Keyboard::isKeyPressed(Keyboard::D))))
        {
            pressed = true;
            direction = DOWN_RIGHT;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left) ||
            Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
        {
            pressed = true;
            direction = UP_LEFT;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) && (Keyboard::isKeyPressed(Keyboard::Right))) ||
            (Keyboard::isKeyPressed(Keyboard::W) && (Keyboard::isKeyPressed(Keyboard::D))))
        {
            pressed = true;
            direction = UP_RIGHT;
        }
        if (event.type == Event::KeyReleased)
        {
            direction = STOP;
        }
    }

    void checkBounds() override
    {
        if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getTextureRect().getSize().x>1920)
        {
            direction = STOP;
        }
        if (sprite.getPosition().y < 0 || sprite.getPosition().y + sprite.getTextureRect().getSize().y>1080)
        {
            direction = STOP;
        }
    }

};
