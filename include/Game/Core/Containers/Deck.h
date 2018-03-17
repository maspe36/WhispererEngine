//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_DECK_H
#define WHISPERERENGINE_DECK_H


#include "../../Utilities/Exportable.h"

class Card;
class Player;

class Deck
        : public Exportable,
          public std::enable_shared_from_this<Deck>
{
public:
    std::shared_ptr<Player> player;
    std::string id;
    std::string name;
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    void shuffle();
    std::shared_ptr<Card> draw();
    int count();

    explicit Deck(const std::shared_ptr<Player>& player);
    Deck();
    ~Deck();
};


#endif //WHISPERERENGINE_DECK_H
