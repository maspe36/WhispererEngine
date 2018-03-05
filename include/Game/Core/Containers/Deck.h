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
    std::string deckID;
    std::string deckName;
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    Deck(std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck(std::string deckName, std::string deckID, std::vector<std::shared_ptr<Card>> cards);
    Deck();
    ~Deck();
};


#endif //WHISPERERENGINE_DECK_H
