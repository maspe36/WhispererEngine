//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CARDMOVEDMESSAGE_H
#define WHISPERERENGINE_CARDMOVEDMESSAGE_H


#include "../Message.h"

class Card;
class Container;

class CardMovedMessage
        : public Message
{
public:
    std::shared_ptr<Container> origin;
    std::shared_ptr<Container> destination;
    std::shared_ptr<Card> card;
    std::string playerTag;

    explicit CardMovedMessage(const std::shared_ptr<Container>& origin,
                              const std::shared_ptr<Container>& destination,
                              const std::shared_ptr<Card>& card);
    ~CardMovedMessage();
};


#endif //WHISPERERENGINE_CARDMOVEDMESSAGE_H
