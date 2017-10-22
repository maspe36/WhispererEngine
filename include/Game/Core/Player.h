//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_PLAYER_H
#define WHISPERERENGINE_PLAYER_H


#include "../../Network/Client.h"

#include <string>
#include <vector>

class Board;
class Card;
class Game;
class Mana;

class Client;

/* Represents a single player. */
class Player
{
public:
    std::string name;
    Client *client;
    Game *game;

    Mana *availableMana;
    Mana *totalMana;
    Board *board;
    std::vector<Card*> hand;

    Player(std::string name, Client::pointer client);
    ~Player();
};


#endif //WHISPERERENGINE_PLAYER_H
