//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_BOARD_H
#define WHISPERERENGINE_BOARD_H


#include <vector>
#include <memory>
#include "../Utilities/Exportable.h"

class Card;
class Constant;
class Creature;

class CreatureZone;
class Deck;
class Graveyard;

/* Handles a single players cards in play. */
class Board
        : public Exportable,
          public std::enable_shared_from_this<Board>
{
public:
    std::shared_ptr<CreatureZone> creatures;
    std::shared_ptr<Deck> deck;
    std::shared_ptr<Graveyard> graveyard;

    json getJSON() override;

    void playCard(std::shared_ptr<Card> card);

    Board();
    virtual ~Board();
};


#endif //WHISPERERENGINE_BOARD_H
