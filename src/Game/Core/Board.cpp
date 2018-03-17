//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Board.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Derived/Card/Creature.h"

void Board::playCard(std::shared_ptr<Card> card)
{
    if (auto creature = std::dynamic_pointer_cast<Creature>(card))
    {
        creatures.push_back(creature);
    }
}

Board::Board(const std::shared_ptr<Player>& player)
        : player(player),
          deck(std::make_shared<Deck>(player))
{
}

Board::~Board()
= default;
