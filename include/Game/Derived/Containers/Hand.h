//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_HAND_H
#define WHISPERERENGINE_HAND_H


#include "../../Core/Container.h"

class Card;

class Hand
        : public Container
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    std::shared_ptr<Card> findCard(const std::string& tag);
    void addCard(std::shared_ptr<Card> card);

    int count();

    Hand();
    ~Hand();
};


#endif //WHISPERERENGINE_HAND_H
