//
// Created by Sam on 3/28/2018.
//

#include "../../../../../include/Game/Derived/Event/PlayerEvents/DrawEvent.h"
#include "../../../../../include/Game/Core/Card.h"
#include "../../../../../include/Game/Core/Game.h"
#include "../../../../../include/Game/Core/Player.h"
#include "../../../../../include/Network/Client.h"
#include "../../../../../include/Network/Derived/DrawMessage.h"

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
