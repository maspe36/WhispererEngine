//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CARD_H
#define WHISPERERENGINE_CARD_H


#include <string>
#include <vector>
#include <memory>
#include "Mana.h"
#include "../Utilities/Exportable.h"

class Effect;
class Player;
class Modifier;

/* Represents a single card. */
class Card
        : public Exportable,
          public std::enable_shared_from_this<Card>
{
public:
    std::string pythonName;
    std::string name;
    std::string text;
    Mana mana;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Effect>> effects;
    std::vector<std::shared_ptr<Modifier>> modifiers;

    json getJSON() override;

    Card(std::string name, std::string text, Mana mana);
    virtual ~Card();
};


#endif //WHISPERERENGINE_CARD_H
