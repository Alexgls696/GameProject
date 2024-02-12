#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <iostream>

enum Direction //НАПРАВЛЕНИЯ ДВИЖЕНИЯ
{
    STOP,LEFT,RIGHT,UP,DOWN
};

#define MAPS_COUNT 4
#define WIDTH 1920
#define HEIGHT 1080

using namespace std;
using namespace sf;



