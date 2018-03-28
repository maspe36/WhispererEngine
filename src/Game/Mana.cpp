//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Mana.h"

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

void Mana::increaseMana(Mana mana)
{
    if (mana.black > 0)
    {
        black++;
    }
    else if (mana.blue > 0)
    {
        blue++;
    }
    else if (mana.brown > 0)
    {
        brown++;
    }
    else if (mana.green > 0)
    {
        green++;
    }
    else if (mana.red > 0)
    {
        red++;
    }
    else if (mana.white > 0)
    {
        white++;
    }
}

bool Mana::canPay(Mana mana)
{
    return (black >= mana.black &&
            blue  >= mana.blue &&
            brown >= mana.brown &&
            green >= mana.green &&
            red   >= mana.red &&
            white >= mana.white);
}

json Mana::getJSON()
{
    json manaJSON;

    manaJSON["black"] = black;
    manaJSON["blue"] = blue;
    manaJSON["brown"] = brown;
    manaJSON["green"] = green;
    manaJSON["red"] = red;
    manaJSON["white"] = white;

    return manaJSON;
}

int Mana::getTotalCount()
{
    return black +
           blue +
           brown +
           green +
           red +
           white;
}

Mana::Mana(int black, int blue, int brown, int green, int red, int white)
        : black(black), blue(blue), brown(brown), green(green), red(red), white(white), individualManaLimit(10)
{
}

bool Mana::withinIndividualLimit()
{
    return (black < individualManaLimit &&
            blue  < individualManaLimit &&
            brown < individualManaLimit &&
            green < individualManaLimit &&
            red   < individualManaLimit &&
            white < individualManaLimit);
}

Mana::~Mana()
= default;
