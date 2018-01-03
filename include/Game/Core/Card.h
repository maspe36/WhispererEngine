//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CARD_H
#define WHISPERERENGINE_CARD_H


#include <string>
#include <vector>
#include "Mana.h"
#include "Taggable.h"

class Effect;
class Player;
class Mana;
class Modifier;

/* Represents a single card. */
class Card: public Taggable
{
public:
    std::string name;
    std::string text;
    Mana mana;
    Player* player;
    std::vector<Effect*> effects;
    std::vector<Modifier*> modifiers;

    void addEffect(Effect *effect);
    void addModifier(Modifier *modifier);

    Card(std::string name, std::string text, Mana mana);

    virtual ~Card();
};


#endif //WHISPERERENGINE_CARD_H
