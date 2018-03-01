//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_PLAYER_H
#define WHISPERERENGINE_PLAYER_H


#include "../../Network/Client.h"
#include "../Utilities/Taggable.h"
#include "Containers/Hand.h"
#include "Mana.h"
#include "Board.h"

#include <string>
#include <vector>

class Card;
class Game;

/* Represents a single player. */
class Player: public Taggable
{
public:
    std::string name;
    Client::pointer client;
    std::shared_ptr<Game> game;

    Mana availableMana;
    Mana totalMana;
    std::shared_ptr<Board> board;
    std::shared_ptr<Hand> hand;

    explicit Player(Client::pointer client);
    ~Player();
};


#endif //WHISPERERENGINE_PLAYER_H
