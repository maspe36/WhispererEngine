//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_ACTION_H
#define WHISPERERENGINE_ACTION_H


#include <vector>

class Card;
class Player;

/* A slice in time of an action to the current game state. */
class Action
{
public:
    std::vector<Card*> cards;
    std::vector<Player*> players;

    Action();
    ~Action();
};


#endif //WHISPERERENGINE_ACTION_H
