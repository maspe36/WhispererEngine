//
// Created by Sam on 1/27/2018.
//

#ifndef WHISPERERENGINE_AUTHMESSAGE_H
#define WHISPERERENGINE_AUTHMESSAGE_H


#include "../Message.h"

class AuthMessage
        : public Message
{
public:
    std::string token;

    explicit AuthMessage(const json& newJSON);
    ~AuthMessage() override;
};


#endif //WHISPERERENGINE_AUTHMESSAGE_H
