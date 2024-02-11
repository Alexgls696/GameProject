#pragma once
#pragma once
#include "Players.h"
#include "../Library.h"
#include "../Maps/InvisibilityMap.h";

class PlayerInvisibility : public Players
{
private:
    Texture texture;
    double speed;
    bool is_visibility;
    Map* map;
    Clock clock;
    float time1;
    Clock clock_fps;
    float time_fps;

public:
    PlayerInvisibility(Map* map)
    {
        texture.loadFromFile("Textures/style_sheet.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 38, 47, 56));
        speed = 0.25;
        this->map = map;
        sprite.setOrigin(sprite.getPosition().x + sprite.getTextureRect().width / 2,
                         sprite.getPosition().y + sprite.getTextureRect().height / 2);
        sprite.setColor(Color(255, 255, 255, 0));
        is_visibility = true;
    }

    void draw(RenderWindow& window)
    {
        window.draw(sprite);
        time1 = clock.getElapsedTime().asSeconds();;
        if (is_visibility) {
            if (time1 < 0.5) {
                sprite.setColor(Color(255, 255, 255, time1 * 2 * 255));
            }
            else if (time1 < 1) {
                sprite.setColor(Color(255, 255, 255, 255));
            }
            else if (time1 < 1.5) {
                sprite.setColor(Color(255, 255, 255, (1 - ((time1 - 1) * 2)) * 255));
            }
            else {
                is_visibility = false;
                sprite.setColor(Color(255, 255, 255, 0));
            }
        }
        if (time1 > 4) {
            clock.restart();
            is_visibility = true;
        }
    }

    void move_right(float time)
    {
        int xTexture = int(sprite.getPosition().x / 40) % 3;
        sprite.setTextureRect(IntRect(xTexture * 47, 233, 47, 56));
        Object obj;
        obj.SetPosition(sprite.getPosition().x - 47 / 2 + 12, sprite.getPosition().y - 28,
                        sprite.getPosition().x + speed * time + 47 / 2 - 12, sprite.getPosition().y + 28);
        if (map->is_not_overlap(obj, map->get_count_objects()) &&
            map->is_not_overlap_bonus(obj, map->get_count_bonus()))
        {
            sprite.move(speed * time, 0);
        }
    }

    void move_left(float time)
    {
        int xTexture = int(sprite.getPosition().x / 40) % 3;
        sprite.setTextureRect(IntRect(xTexture * 47, 137, 47, 56));
        Object obj;
        obj.SetPosition(sprite.getPosition().x - speed * time - 47 / 2 + 12, sprite.getPosition().y - 28,
                        sprite.getPosition().x + 47 / 2 - 12, sprite.getPosition().y + 28);
        if (map->is_not_overlap(obj, map->get_count_objects()) &&
            map->is_not_overlap_bonus(obj, map->get_count_bonus()))
        {
            sprite.move(-speed * time, 0);
        }
    }

    void move_up(float time)
    {
        int xTexture = int(sprite.getPosition().y / 40) % 3;
        sprite.setTextureRect(IntRect(xTexture * 47, 329, 47, 56));
        Object obj;
        obj.SetPosition(sprite.getPosition().x - 47 / 2 + 12, sprite.getPosition().y - 28 - speed * time,
                        sprite.getPosition().x + 47 / 2 - 12, sprite.getPosition().y + 28);
        if (map->is_not_overlap(obj, map->get_count_objects()) &&
            map->is_not_overlap_bonus(obj, map->get_count_bonus()))
        {
            sprite.move(0, -speed * time);
        }
    }

    void move_down(float time)
    {
        int xTexture = int(sprite.getPosition().y / 40) % 3;
        sprite.setTextureRect(IntRect(xTexture * 47, 39, 47, 56));
        Object obj;
        obj.SetPosition(sprite.getPosition().x - 47 / 2 + 12, sprite.getPosition().y - 28,
                        sprite.getPosition().x + 47 / 2 - 12, sprite.getPosition().y + 28 + speed * time);
        if (map->is_not_overlap(obj, map->get_count_objects()) &&
            map->is_not_overlap_bonus(obj, map->get_count_bonus()))
        {
            sprite.move(0, speed * time);
        }
    }

    void move()
    {
        time_fps = clock_fps.getElapsedTime().asMicroseconds() / 1500;
        clock_fps.restart();
        Object obj;
        obj.SetPosition(sprite.getPosition().x - 47 / 2 - 5, sprite.getPosition().y - 28 - 5,
                        sprite.getPosition().x + 47 / 2 + 5, sprite.getPosition().y + 28 + 5);
        if (!map->is_not_overlap_bonus(obj, map->get_count_bonus()))
        {
            map->bonus_open(map->number_bonus(obj, map->get_count_bonus()));
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            move_left(time_fps);
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            move_right(time_fps);
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            move_up(time_fps);
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            move_down(time_fps);
        }
    }

    void Direction(Event& event) override
    {
        if (Keyboard::isKeyPressed(sf::Keyboard::A) || Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction = LEFT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            direction = UP;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::W) || Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction = RIGHT;
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::S) || Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            direction = DOWN;
        }
    }
};
