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
class Player;

/* Handles a single players cards in play. */
class Board
        : public std::enable_shared_from_this<Board>
{
public:
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Constant>> constants;
    std::vector<std::shared_ptr<Creature>> creatures;
    std::shared_ptr<Deck> deck;
    std::vector<std::shared_ptr<Card>> graveyard;

    void playCard(std::shared_ptr<Card> card);

    explicit Board(const std::shared_ptr<Player>& player);
    virtual ~Board();
};


#endif //WHISPERERENGINE_BOARD_H
