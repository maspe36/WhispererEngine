//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_GAME_H
#define WHISPERERENGINE_GAME_H


#include <vector>

class Event;
class Card;
class Converter;
class Factory;
class Player;

class Server;

/* Overall handler for game interactions. */
class Game
{
public:
    std::vector<Player*> players;
    std::vector<Event*> history;
    std::vector<void (*)()> stack;
    std::vector<Card*> cardOrder;
    Factory *factory;
    Converter *converter;
    Server *server;

    Game(std::vector<Player*> players);
    ~Game();
};


#endif //WHISPERERENGINE_GAME_H
