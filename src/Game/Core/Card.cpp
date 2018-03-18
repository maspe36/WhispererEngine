//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Card.h"


json Card::getJSON()
{
    json rawJSON;

    rawJSON["pythonName"] = pythonName;
    rawJSON["name"] = name;
    rawJSON["text"] = text;
    rawJSON["tag"] = tag;
    rawJSON["mana"] = mana.getJSON();

    return rawJSON;
}

Card::Card(std::string name, std::string text, Mana mana)
        : name(std::move(name)), text(std::move(text)), mana(mana)
{
}

Card::~Card()
= default;
