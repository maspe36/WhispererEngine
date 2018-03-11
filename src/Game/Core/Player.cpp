//
// Created by Sam on 9/25/2017.
//

#include <utility>
#include <iostream>

#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Board.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Network/Derived/ChatMessage.h"
#include "../../../include/Network/Derived/PlayCardMessage.h"

void Player::draw()
{
    hand->addCard(board->deck->draw());
}

void Player::draw(int count)
{
    for (int i = 0; i < count; i++)
    {
        draw();
    }
}

void Player::playCard(const json &rawJSON)
{
    if (shared_from_this() == game->activePlayer)
    {
        PlayCardMessage moveCardMessage(rawJSON);
        auto card = hand->findCard(moveCardMessage.cardTag);

        if (availableMana.canPay(card->mana))
        {
            availableMana.payMana(card->mana);
            board->playCard(card);
        }
    }
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
    opponentJSON["name"] = name;
    opponentJSON["tag"] = tag;
    opponentJSON["health"] = health;
    opponentJSON["handCount"] = hand->count();
    opponentJSON["deckCount"] = board->deck->count();
    opponentJSON["mana"] = getManaJSON();

    return opponentJSON;
}

json Player::getManaJSON()
{
    json manaJSON;
    manaJSON["available"] = availableMana.getJSON();
    manaJSON["total"] = totalMana.getJSON();

    return manaJSON;
}

Player::Player(std::shared_ptr<Client> client)
        : client(client),
          name(client->name),
          availableMana(1,1,1,1,1,1),
          totalMana(1,1,1,1,1,1),
          board(std::make_shared<Board>()),
          hand(std::make_shared<Hand>()),
          health(30)
{
}

Player::~Player()
= default;
