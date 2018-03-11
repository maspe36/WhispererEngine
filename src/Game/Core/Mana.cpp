//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Mana.h"

bool Mana::operator == (const Mana &other) const
{
    return black == other.black
           && blue == other.blue
           && brown == other.brown
           && green == other.green
           && red == other.red
           && white == other.white;
}

void Mana::payMana(Mana mana)
{
    black -= mana.black;
    blue -= mana.blue;
    brown -= mana.brown;
    green -= mana.green;
    red -= mana.red;
    white -= mana.white;
}

Mana::Mana(int black, int blue, int brown, int green, int red, int white)
        : black(black), blue(blue), brown(brown), green(green), red(red), white(white)
{
}

bool Mana::canPay(Mana mana)
{
    return (black > mana.black &&
            blue > mana.blue &&
            brown > mana.brown &&
            green > mana.green &&
            red > mana.red &&
            white > mana.white);
}

Mana::~Mana()
= default;
