#pragma once
#include "Object.h"
#include "../Library.h"
class Bonuses : public Object
{
public:
    Bonuses() : Object() {

    }
    virtual void draw(RenderWindow&window) = 0;
};
