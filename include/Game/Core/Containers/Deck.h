//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_DECK_H
#define WHISPERERENGINE_DECK_H


#include "../../Utilities/Exportable.h"

class Card;

class Deck
        : public Exportable,
          public std::enable_shared_from_this<Deck>
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    explicit Deck(std::vector<std::shared_ptr<Card>> cards);
    ~Deck();
};


#endif //WHISPERERENGINE_DECK_H
