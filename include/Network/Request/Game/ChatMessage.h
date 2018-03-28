//
// Created by Sam on 3/3/2018.
//

#ifndef WHISPERERENGINE_CHATMESSAGE_H
#define WHISPERERENGINE_CHATMESSAGE_H


#include "../../Message.h"

class ChatMessage
        : public Message
{
public:
    std::string text;

    explicit ChatMessage(const json& newJSON);
    ~ChatMessage() override;
};

#endif //WHISPERERENGINE_CHATMESSAGE_H
