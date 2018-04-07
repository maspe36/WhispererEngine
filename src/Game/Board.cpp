//
// Created by Sam on 9/25/2017.
//

#include "../../include/Game/Board.h"
#include "../../include/Game/Card.h"
#include "../../include/Game/Card/Creature.h"
#include "../../include/Game/Container/CreatureZone.h"
#include "../../include/Game/Container/Deck.h"
#include "../../include/Game/Container/Graveyard.h"

void Board::playCard(std::shared_ptr<Card> card)
{
    if (auto creature = std::dynamic_pointer_cast<Creature>(card))
    {
        creatures->addCard(creature);
    }
}

Board::Board()
        : creatures(std::make_shared<CreatureZone>()),
          deck(std::make_shared<Deck>()),
          graveyard(std::make_shared<Graveyard>())

{
}

json Board::getJSON()
{
    json boardJSON;

    boardJSON["creatures"] = creatures->getJSON();
    boardJSON["graveyard"] = graveyard->getJSON();

    return boardJSON;
}

Board::~Board()
= default;
