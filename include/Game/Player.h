//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_PLAYER_H
#define WHISPERERENGINE_PLAYER_H


#include "Mana.h"
#include "Board.h"
#include "../Network/Message.h"
#include "Utilities/Exportable.h"

#include <string>
#include <vector>

class Card;
class Client;
class Game;
class Hand;

/* Represents a single player. */
class Player
        : public Exportable,
          public std::enable_shared_from_this<Player>
{
public:
    typedef void (Player::*func)();
    typedef void (Player::*protocolFunc)(const json& rawJSON);

    std::string name;
    std::shared_ptr<Client> client;
    std::shared_ptr<Game> game;

    Mana availableMana;
    Mana totalMana;
    std::shared_ptr<Board> board;
    std::shared_ptr<Hand> hand;
    int health;

    void startGameSetup();
    void draw();
    void draw(int count);
    void startTurn();
    void refillMana();
    void refreshCreatures();
    void surrender();
    void quit();

    void refreshDeck();

    // Protocol functions
    void playCard(const json &rawJSON);
    void endTurn(const json &rawJSON);
    void sendChatMessage(const json& rawJSON);
    void fightPlayer(const json& rawJSON);
    void fightCreature(const json& rawJSON);
    void surrender(const json& rawJSON);

    json getState();
    json getOpponentState();
    json getManaJSON();

    explicit Player(std::shared_ptr<Client> client);
    ~Player();

private:
    void internalDraw();
    void internalDraw(int count);

    void destroyCreature(const std::shared_ptr<Creature> &target) const;
};


#endif //WHISPERERENGINE_PLAYER_H
