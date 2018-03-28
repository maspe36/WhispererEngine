//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CARDMOVEDMESSAGE_H
#define WHISPERERENGINE_CARDMOVEDMESSAGE_H


#include "../../Message.h"

class Card;
class Container;

class CardMovedMessage
        : public Message
{
public:
    explicit CardMovedMessage(const std::shared_ptr<Container>& origin,
                              const std::shared_ptr<Container>& destination,
                              const std::shared_ptr<Card>& card);
    ~CardMovedMessage();

private:
    int getZoneID(const std::shared_ptr<Container>& container);
};


#endif //WHISPERERENGINE_CARDMOVEDMESSAGE_H
