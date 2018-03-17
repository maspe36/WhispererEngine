//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_HAND_H
#define WHISPERERENGINE_HAND_H


#include "../../Utilities/Exportable.h"

class Card;
class Player;

class Hand
        : public Exportable,
          public std::enable_shared_from_this<Hand>
{
public:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON();

    std::shared_ptr<Card> findCard(const std::string& tag);
    void addCard(std::shared_ptr<Card> card);
    void removeCard(std::shared_ptr<Card> card);

    int count();

    explicit Hand(const std::shared_ptr<Player>& player);
    ~Hand();
};


#endif //WHISPERERENGINE_HAND_H
