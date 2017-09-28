//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_GAME_H
#define WHISPERERENGINE_GAME_H


#include <vector>

class Action;
class Card;
class Factory;
class Player;

class Server;

/* Overall handler for game interactions. */
class Game
{
public:
    std::vector<Player*> players;
    std::vector<Action*> history;
    std::vector<void (*)()> stack;
    std::vector<Card*> cardOrder;
    Factory *factory;
    Server *server;

    Game(std::vector<Player*> players);
    ~Game();
};


#endif //WHISPERERENGINE_GAME_H
