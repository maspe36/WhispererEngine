//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_BOARD_H
#define WHISPERERENGINE_BOARD_H


#include <vector>
#include <memory>

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
    std::vector<std::shared_ptr<Card>> deck;
    std::vector<std::shared_ptr<Card>> graveyard;

    Board();
    ~Board();
};


#endif //WHISPERERENGINE_BOARD_H
