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
#include "../../include/Game/Container/Graveyard.h"
#include "../../include/Network/Client.h"
#include "../../include/Network/Request/Game/ChatMessage.h"
#include "../../include/Network/Request/Game/PlayCardMessage.h"
#include "../../include/Network/Request/Game/FightPlayerMessage.h"
#include "../../include/Game/Event/Player/DrawEvent.h"
#include "../../include/Game/Event/Player/PlayCardEvent.h"
#include "../../include/Game/Event/Player/PlayerAttackedEvent.h"
#include "../../include/Game/Event/Game/StartTurnEvent.h"
#include "../../include/Game/Event/Game/EndTurnEvent.h"
#include "../../include/Network/Request/Game/FightCreatureMessage.h"
#include "../../include/Game/Event/Player/CreatureAttackedEvent.h"
#include "../../include/Game/Event/Game/CreatureDestroyedEvent.h"
#include "../../include/Game/Event/Game/EndGameEvent.h"

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
        else
        {
            throw std::runtime_error("Insufficient mana to play " + card->name);
        }
    }
    else
    {
        throw std::runtime_error("You cannot play a card when it was not your turn");
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

    std::vector<std::shared_ptr<Player>> alive;

    if (game->isGameOver())
    {
        game->endGame();
    }
}

void Player::fightCreature(const json &rawJSON)
{
    FightCreatureMessage fightCreatureMessage(rawJSON);

    auto attackingPlayer = game->findPlayer(fightCreatureMessage.attackingPlayerTag);
    auto attackingCard = attackingPlayer->board->creatures->findCard(fightCreatureMessage.attackingCardTag);
    auto attacker = std::dynamic_pointer_cast<Creature>(attackingCard);
    std::shared_ptr<Creature> target;

    for (const auto& player : game->players)
    {
        try
        {
            auto card = player->board->creatures->findCard(fightCreatureMessage.attackedCardTag);
            target = std::dynamic_pointer_cast<Creature>(card);
        }
        catch (const std::runtime_error& ex)
        {/* Eat this because findCard throws a runtime error if the card is not found */}
    }

    if (!target)
    {
        throw std::runtime_error("Cannot find attacked card with tag '" + fightCreatureMessage.attackedCardTag + "'");
    }

    if (attacker->player == target->player)
    {
        throw std::runtime_error("You cannot attack your own creatures");
    }

    attacker->attack(target);

    CreatureAttackedEvent creatureAttackedEvent(game, target, attacker);
    game->eventHandler(std::make_shared<CreatureAttackedEvent>(creatureAttackedEvent));

    if (target->defenseStat <= 0)
    {
        destroyCreature(target);
    }

    if (attacker->defenseStat <= 0)
    {
        destroyCreature(attacker);
    }
}

void Player::surrender(const json &rawJSON)
{
    game->surrender(shared_from_this());
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
    opponentJSON["avatarURL"] = client->avatarURL;
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

void Player::destroyCreature(const std::shared_ptr<Creature> &target) const
{
    auto targetOwner = target->player;
    targetOwner->board->graveyard->cards.push_back(target);
    targetOwner->board->creatures->removeCard(target);

    CreatureDestroyedEvent creatureDestroyedEvent(game, target);
    game->eventHandler(std::make_shared<CreatureDestroyedEvent>(creatureDestroyedEvent));
}
