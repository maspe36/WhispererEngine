//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_BOARD_H
#define WHISPERERENGINE_BOARD_H


#include <vector>

class Card;
class Constant;
class Creature;


class Board
{
public:
    std::vector<Constant*> constants;
    std::vector<Creature*> creatures;
    std::vector<Card*> deck;
    std::vector<Card*> graveyard;

    Board();
    ~Board();
};


#endif //WHISPERERENGINE_BOARD_H
