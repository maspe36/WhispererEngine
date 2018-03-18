//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_DECK_H
#define WHISPERERENGINE_DECK_H


#include "../../Core/Container.h"

class Card;

class Deck
        : public Container
{
public:
    std::string id;
    std::string name;
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    void shuffle();
    std::shared_ptr<Card> draw();
    int count();

    Deck(std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck(std::string deckName, std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck();
    ~Deck();
};


#endif //WHISPERERENGINE_DECK_H
