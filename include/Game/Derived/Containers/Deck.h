//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_DECK_H
#define WHISPERERENGINE_DECK_H


#include "../../Core/Container.h"

class Deck
        : public Container
{
public:
    std::string id;
    std::string name;

    json getJSON();

    std::shared_ptr<Card> draw();

    Deck(std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck(std::string deckName, std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck();
    ~Deck();
};


#endif //WHISPERERENGINE_DECK_H
