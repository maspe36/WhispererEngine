//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Mana.h"


void Mana::payMana(Mana *mana)
{
    black -= mana->black;
    blue -= mana->blue;
    brown -= mana->brown;
    green -= mana->green;
    red -= mana->red;
    white -= mana->white;
}

Mana::Mana(int black, int blue, int brown, int green, int red, int white)
        : black(black), blue(blue), brown(brown), green(green), red(red), white(white)
{
}

Mana::~Mana()
= default;
