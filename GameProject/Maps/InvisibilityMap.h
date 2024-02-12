#pragma once
#include "Map.h"
#include <fstream>
#include "../Bonuses/InvisibilityBonus.h"
#include "../Obstacles/InvisibilityObstacles.h"
#include "../Players/PlayerInvisibility.h"

class InvisibilityMap : public Map
{
private:
    Texture* textures_objects;
    Texture bonus;
    Texture open_bonus;
    Sprite* sprites_objects;
    Sprite* sprites_bonus;
    Object* objects;
    Object* objects_bonus;
    int count_objects;
    int min_distance_objects;
    int count_bonus;
    friend class PlayerInvisibility;
public:
    InvisibilityMap()
    {
        name = "InvisibilityMap";
        rect.setFillColor(Color::Cyan);
        player= new PlayerInvisibility(this);
        srand(time(0));
        ifstream file("objects.txt");
        file >> count_objects;
        file >> min_distance_objects;
        file >> count_bonus;
        textures_objects = new Texture[count_objects];
        sprites_objects = new Sprite[count_objects];
        objects = new Object[count_objects];
        sprites_bonus = new Sprite[count_bonus];
        objects_bonus = new Object[count_bonus];
        Texture map_texture();
        texture.loadFromFile("Textures/map.png");
        rect.setTexture(&texture);
        string name_file;
        int width, height, count_objects_file, x, y;
        for (int i = 0; file >> name_file >> width >> height >> count_objects_file; ) {
            for (int j = 0; j < count_objects_file; j++) {
                textures_objects[i].loadFromFile(name_file);
                sprites_objects[i].setTexture(textures_objects[i]);
                do {
                    x = ((rand() % 29) + 1) * 32;
                    y = ((rand() % 17) + 1) * 32;
                    Object obj;
                    obj.SetPosition(rect.getPosition().x + x - min_distance_objects, rect.getPosition().y + y - min_distance_objects,
                        rect.getPosition().x + x + width * 32 + min_distance_objects, rect.getPosition().y + y + height * 32 + min_distance_objects);
                    if (is_not_overlap(obj, i)) {
                        break;
                    }
                } while (true);
                obstacles.push_back(new InvisibilityObstacles(&textures_objects[i]));
                obstacles[i]->getSprite().setPosition(rect.getPosition().x + x, rect.getPosition().y + y);
                objects[i].SetPosition(rect.getPosition().x + x, rect.getPosition().y + y, rect.getPosition().x + x + width * 32, rect.getPosition().y + y + height * 32);
                sprites_objects[i].setPosition(rect.getPosition().x + x, rect.getPosition().y + y);
                i++;
            }
        }
        bonus.loadFromFile("Textures/chest_close.png");
        open_bonus.loadFromFile("Textures/chest_open.png");
        for (int i = 0; i < count_bonus; i++) {
            do {
                x = ((rand() % 30) + 1) * 32;
                y = ((rand() % 17) + 1) * 32;
                Object obj;
                obj.SetPosition(rect.getPosition().x + x - min_distance_objects, rect.getPosition().y + y - min_distance_objects,
                    rect.getPosition().x + x + width * 32 + min_distance_objects, rect.getPosition().y + y + height * 32 + min_distance_objects);
                if (is_not_overlap(obj, count_objects) && is_not_overlap_bonus(obj, i)) {
                    break;
                }
            } while (true);
            bonuses.push_back(new InvisibilityBonus);
            bonuses[i]->getSprite().setPosition(rect.getPosition().x + x + 16, rect.getPosition().y + y + 16);
            sprites_bonus[i].setTexture(bonus);
            sprites_bonus[i].setPosition(rect.getPosition().x + x, rect.getPosition().y + y);
            objects_bonus[i].SetPosition(rect.getPosition().x + x, rect.getPosition().y + y, rect.getPosition().x + x + 32, rect.getPosition().y + y + 32);
        }
        file.close();
    }

    void draw(RenderWindow& window) {
        window.draw(rect);
        for (int i = 0; i < count_objects; i++) {
            window.draw(sprites_objects[i]);
        }
        for (int i = 0; i < count_bonus; i++) {
            window.draw(sprites_bonus[i]);
        }
    }
    bool is_not_overlap(Object obj, int count = 12) {
        if ((obj.x2 - min_distance_objects > rect.getPosition().x + 960 - 32) || (obj.y2 - min_distance_objects > rect.getPosition().y + 540 - 32)) {
            return false;
        }
        for (int i = 0; i < count; i++) {
            if (obj.x1 < objects[i].x2 && obj.x2 > objects[i].x1 &&
                obj.y1 < objects[i].y2 && obj.y2 > objects[i].y1) {
                return false;
            }
        }
        return true;
    }
    bool is_not_overlap_bonus(Object obj, int count = 5) {
        for (int i = 0; i < count; i++) {
            if (obj.x1 < objects_bonus[i].x2 && obj.x2 > objects_bonus[i].x1 &&
                obj.y1 < objects_bonus[i].y2 && obj.y2 > objects_bonus[i].y1) {
                return false;
            }
        }
        return true;
    }
    int number_bonus(Object obj, int count) {
        for (int i = 0; i < count; i++) {
            if (obj.x1 < objects_bonus[i].x2 && obj.x2 > objects_bonus[i].x1 &&
                obj.y1 < objects_bonus[i].y2 && obj.y2 > objects_bonus[i].y1) {
                return i;
            }
        }
        return 0;
    }
    int get_count_objects() {
        return count_objects;
    }
    int get_count_bonus() {
        return count_bonus;
    }
    void bonus_open(int number_bonus) {
        sprites_bonus[number_bonus].setTexture(open_bonus);
    }
    bool checking_transition(Players* player) {
        Object obj;
        obj.SetPosition(player->getSprite().getPosition().x - player->getSprite().getTextureRect().width / 2,
            player->getSprite().getPosition().y - player->getSprite().getTextureRect().height / 2,
            player->getSprite().getPosition().x - player->getSprite().getTextureRect().width / 2 + 47,
            player->getSprite().getPosition().y - player->getSprite().getTextureRect().height / 2 + 56);
        if (is_not_overlap(obj, 12) && is_not_overlap_bonus(obj, 5)) {
            return true;
        }
        return false;
    }
    bool check_win() {
        for (int i = 0; i < count_bonus; i++) {
            if (sprites_bonus[i].getTexture() != &open_bonus) {
                return false;
            }
        }
        return true;
    }
    Players*getPlayer() override
    {
        player = new PlayerInvisibility(this);
        return player;
    }
};

