//
// Created by Sam on 9/25/2017.
//

#include <utility>
#include <iostream>

#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Board.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Network/Derived/ChatMessage.h"

void Player::playCard(const json& rawJSON)
{
    std::cout << "Hello from player class" << std::endl;
}

void Player::sendChatMessage(const json &rawJSON)
{
    // Format chat message with the sender name before broadcasting it to all players
    ChatMessage chatMessage(rawJSON);
    chatMessage.rawJSON[Message::DATA_KEY]["text"] = name + ": " + chatMessage.text;

    game->writePlayers(chatMessage.getJSON());
}

json Player::getOpponentJSON()
{
    json opponentJSON;

    opponentJSON["playerID"] = tag;
    opponentJSON["playerName"] = name;

    return opponentJSON;
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
