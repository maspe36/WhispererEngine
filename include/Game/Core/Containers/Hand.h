//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_HAND_H
#define WHISPERERENGINE_HAND_H


#include "../../Utilities/Exportable.h"

class Card;

class Hand
        : public Exportable,
          public std::enable_shared_from_this<Hand>
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    void addCard(std::shared_ptr<Card> card);

    Hand();
    ~Hand();
};


#endif //WHISPERERENGINE_HAND_H
