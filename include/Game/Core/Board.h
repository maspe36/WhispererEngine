//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_BOARD_H
#define WHISPERERENGINE_BOARD_H


#include <vector>
#include <memory>
#include "Containers/Deck.h"

class Card;
class Constant;
class Creature;

/* Handles a single players cards in play. */
class Board
        : public std::enable_shared_from_this<Board>
{
public:
    std::vector<std::shared_ptr<Constant>> constants;
    std::vector<std::shared_ptr<Creature>> creatures;
    std::shared_ptr<Deck> deck;
    std::vector<std::shared_ptr<Card>> graveyard;

    void playCard(std::shared_ptr<Card> card);

    Board();
    virtual ~Board();
};


#endif //WHISPERERENGINE_BOARD_H
