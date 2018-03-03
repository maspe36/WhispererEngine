//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_GAME_H
#define WHISPERERENGINE_GAME_H


#include <vector>
#include <string>
#include <memory>

class Card;
class Event;
class Effect;
class Player;

class Server;

/* Overall handler for game interactions. */
class Game
{
public:
    std::vector<std::shared_ptr<Player>> players;
    std::vector<Event*> history;
    std::vector<Effect*> stack;
    std::vector<std::shared_ptr<Card>> cardOrder;
    std::shared_ptr<Server> server;

    void WritePlayers(const std::string& data);

    Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server);
    ~Game();
};


#endif //WHISPERERENGINE_GAME_H
