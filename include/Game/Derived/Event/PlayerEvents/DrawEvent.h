//
// Created by Sam on 3/28/2018.
//

#ifndef WHISPERERENGINE_DRAWEVENT_H
#define WHISPERERENGINE_DRAWEVENT_H


#include <vector>
#include "../../../Core/Event.h"

class Card;
class Player;

class DrawEvent
        : public Event
{
public:
    std::vector<std::shared_ptr<Card>> cards;
    std::shared_ptr<Player> toPlayer;

    void sendMessage() override;

    explicit DrawEvent(const std::shared_ptr<Game>& game, const std::vector<std::shared_ptr<Card>>& cards, const std::shared_ptr<Player>& toPlayer);
    ~DrawEvent();
};


#endif //WHISPERERENGINE_DRAWEVENT_H
