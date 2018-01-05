//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Player.h"

Player::Player(Client::pointer client) : client(std::move(client))
{
}

Player::~Player()
= default;
