//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Board.h"
#include "../../../include/Network/Client.h"

void Player::playCard(const Message& message)
{

}

Player::Player(std::shared_ptr<Client> client)
        : client(client),
          name(client->name),
          availableMana(1,1,1,1,1,1),
          totalMana(1,1,1,1,1,1)
{
    board = std::make_shared<Board>();
}

Player::~Player()
= default;
