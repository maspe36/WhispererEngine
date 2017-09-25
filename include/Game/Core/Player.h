//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_PLAYER_H
#define WHISPERERENGINE_PLAYER_H


#include <string>
#include <vector>

class Board;
class Card;
class Mana;

class Client;


class Player
{
public:
    std::string name;
    Client *client;

    Mana *availableMana;
    Mana *totalMana;
    Board *board;
    std::vector<Card*> deck;
    std::vector<Card*> hand;

    Player(std::string name, Client *client);
    ~Player();
};


#endif //WHISPERERENGINE_PLAYER_H
