//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_GAME_H
#define WHISPERERENGINE_GAME_H


#include <vector>
#include <string>
#include <memory>
#include "Event.h"
#include "../../Network/Message.h"

class Card;
class Event;
class Effect;
class Player;

class Server;

/* Overall handler for game interactions. */
class Game
        : public std::enable_shared_from_this<Game>
{
public:
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Player> activePlayer;
    std::vector<std::shared_ptr<Event>> history;
    std::vector<std::shared_ptr<Effect>> stack;
    std::vector<std::shared_ptr<Card>> cardOrder;
    std::shared_ptr<Server> server;

    std::vector<json> getOpponentJSON(std::shared_ptr<Player> toPlayer);

    void writePlayers(const std::string &data);
    void registerPlayers();

    void eventHandler(Event event);
    void queueEffects(Event event);
    void solveEffects();

    void startGame();
    void changeTurn();

    Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server);
    virtual ~Game();

private:
    void sendStartGameMessage();
    void sendTurnMessage();
};


#endif //WHISPERERENGINE_GAME_H
