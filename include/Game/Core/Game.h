//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_GAME_H
#define WHISPERERENGINE_GAME_H


#include <vector>
#include <string>

class Card;
class Event;
class Effect;
class Player;

class Converter;
class Factory;

class Server;

/* Overall handler for game interactions. */
class Game
{
public:
    std::vector<Player*> players;
    std::vector<Event*> history;
    std::vector<Effect*> stack;
    std::vector<Card*> cardOrder;
    Factory *factory;
    Converter *converter;
    Server *server;

    void WritePlayers(std::string data);

    Game(std::vector<Player*> players, Server *server);
    ~Game();
};


#endif //WHISPERERENGINE_GAME_H
