//
// Created by Sam on 3/28/2018.
//

#include "../../../../include/Game/Event/Player/DrawEvent.h"
#include "../../../../include/Game/Card.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Game/Player.h"
#include "../../../../include/Network/Client.h"
#include "../../../../include/Network/Response/Game/DrawMessage.h"

void DrawEvent::sendMessage()
{
    for (const auto& player : game->players)
    {
        DrawMessage drawMessage(game, cards, toPlayer);

        if (player == toPlayer)
        {
            drawMessage.toSelf();
        }
        else
        {
            drawMessage.toOpponent();
        }

        player->client->write(drawMessage.getJSON());
    }
}

DrawEvent::DrawEvent(const std::shared_ptr<Game> &game, const std::vector<std::shared_ptr<Card>>& cards, const std::shared_ptr<Player>& toPlayer)
        : Event(game), cards(cards), toPlayer(toPlayer)
{
}

DrawEvent::~DrawEvent()
= default;
