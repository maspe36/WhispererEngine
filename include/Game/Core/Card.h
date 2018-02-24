//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CARD_H
#define WHISPERERENGINE_CARD_H


#include <string>
#include <vector>
#include <memory>
#include "Mana.h"
#include "../Utilities/Taggable.h"

class Effect;
class Player;
class Modifier;

/* Represents a single card. */
class Card: public Taggable, public std::enable_shared_from_this<Card>
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
