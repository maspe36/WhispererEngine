//
// Created by Sam on 9/25/2017.
//

#include <utility>
#include <iostream>

#include "../../include/Game/Card.h"
#include "../../include/Game/Player.h"
#include "../../include/Game/Game.h"
#include "../../include/Game/Card/Creature.h"
#include "../../include/Game/Container/Deck.h"
#include "../../include/Game/Container/Hand.h"
#include "../../include/Game/Container/CreatureZone.h"
#include "../../include/Network/Client.h"
#include "../../include/Network/Message/ChatMessage.h"
#include "../../include/Network/Message/PlayCardMessage.h"
#include "../../include/Network/Message/FightPlayerMessage.h"
#include "../../include/Game/Event/Player/DrawEvent.h"
#include "../../include/Game/Event/Player/PlayCardEvent.h"
#include "../../include/Game/Event/Player/PlayerAttackedEvent.h"
#include "../../include/Game/Event/Game/StartTurnEvent.h"
#include "../../include/Game/Event/Game/EndTurnEvent.h"

void Player::startGameSetup()
{
    board->deck->shuffle();
    internalDraw(5);
}

void Player::draw()
{
    internalDraw();

    DrawEvent drawEvent(game, { hand->cards.back() }, shared_from_this());
    game->eventHandler(std::make_shared<DrawEvent>(drawEvent));
}

void Player::draw(int count)
{
    internalDraw(count);

    auto first = hand->cards.end() - count;
    auto last = hand->cards.end();
    std::vector<std::shared_ptr<Card>> drawnCards(first, last);

    DrawEvent drawEvent(game, drawnCards, shared_from_this());
    game->eventHandler(std::make_shared<DrawEvent>(drawEvent));
}

void Player::startTurn()
{
    refillMana();
    refreshCreatures();

    StartTurnEvent startTurnEvent(game);
    game->eventHandler(std::make_shared<StartTurnEvent>(startTurnEvent));

    draw();
}

void Player::refillMana()
{
    availableMana = totalMana;
}

void Player::refreshCreatures()
{
    for (const auto& card : board->creatures->cards)
    {
        const auto& creature = std::dynamic_pointer_cast<Creature>(card);
        creature->availableAttacks = creature->attacks;
        creature->usedAttacks = 0;
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
            hand->removeCard(card);

            if (totalMana.getTotalCount() <= 15 && totalMana.withinIndividualLimit())
            {
                totalMana.increaseMana(card->mana);
            }

            game->cardOrder.push_back(card);

            PlayCardEvent playCardEvent(game, card);
            game->eventHandler(std::make_shared<PlayCardEvent>(playCardEvent));
        }
    }
}

void Player::endTurn(const json &rawJSON)
{
    EndTurnEvent endTurnEvent(game);
    game->eventHandler(std::make_shared<EndTurnEvent>(endTurnEvent));

    game->changeTurn();
}

void Player::sendChatMessage(const json &rawJSON)
{
    // Format chat message with the sender name before broadcasting it to all players
    ChatMessage chatMessage(rawJSON);
    chatMessage.rawJSON[Message::DATA_KEY]["text"] = name + ": " + chatMessage.text;

    game->writePlayers(chatMessage.getJSON());
}

void Player::fightPlayer(const json &rawJSON)
{
    FightPlayerMessage fightPlayerMessage(rawJSON);
    auto player = game->findPlayer(fightPlayerMessage.attackingPlayerTag);
    auto card = board->creatures->findCard(fightPlayerMessage.cardTag);
    auto creature = std::dynamic_pointer_cast<Creature>(card);

    // You can't attack yourself!
    if (player == shared_from_this())
    {
        throw std::runtime_error("You cannot attack yourself");
    }

    creature->attack(player);

    PlayerAttackedEvent playerAttackedEvent(game, card, player);
    game->eventHandler(std::make_shared<PlayerAttackedEvent>(playerAttackedEvent));

    if (player->health <= 0)
    {
        // End the game
    }
}

json Player::getState()
{
    json playerJSON;

    playerJSON["playerTag"] = tag;
    playerJSON["hand"] = hand->getJSON();
    playerJSON["health"] = health;
    playerJSON["deckCount"] = board->deck->count();
    playerJSON["mana"] = getManaJSON();
    playerJSON["board"] = board->getJSON();

    return playerJSON;
}

json Player::getOpponentState()
{
    json opponentJSON;

    opponentJSON["playerTag"] = tag;
    opponentJSON["name"] = name;
    opponentJSON["health"] = health;
    opponentJSON["handCount"] = hand->count();
    opponentJSON["deckCount"] = board->deck->count();
    opponentJSON["mana"] = getManaJSON();
    opponentJSON["board"] = board->getJSON();

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

void Player::internalDraw()
{
    hand->addCard(board->deck->draw());
}

void Player::internalDraw(int count)
{
    for (int i = 0; i < count; i++)
    {
        internalDraw();
    }
}
