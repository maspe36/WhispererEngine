//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Board.h"

Player::Player(Client::pointer client)
        : client(std::move(client)),
          availableMana(1,1,1,1,1,1), totalMana(1,1,1,1,1,1)
{
    board = std::make_shared<Board>();
}

Player::~Player()
= default;
