//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_PLAYER_H
#define WHISPERERENGINE_PLAYER_H


#include "Containers/Hand.h"
#include "Mana.h"
#include "Board.h"
#include "../../Network/Message.h"

#include <string>
#include <vector>

class Card;
class Client;
class Game;

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

    void draw();
    void draw(int count);

    void playCard(const json &rawJSON);
    void sendChatMessage(const json& rawJSON);

    json getState();
    json getOpponentState();
    json getManaJSON();

    explicit Player(std::shared_ptr<Client> client);
    ~Player();
};


#endif //WHISPERERENGINE_PLAYER_H
