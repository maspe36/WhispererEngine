//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Board.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Derived/Card/Creature.h"
#include "../../../include/Game/Derived/Containers/CreatureZone.h"
#include "../../../include/Game/Derived/Containers/Deck.h"
#include "../../../include/Game/Derived/Containers/Graveyard.h"

void Board::playCard(std::shared_ptr<Card> card)
{
    if (auto creature = std::dynamic_pointer_cast<Creature>(card))
    {
        creatures->cards.push_back(creature);
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
