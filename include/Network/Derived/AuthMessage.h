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
    std::string name;
    std::string clientID;

    explicit AuthMessage(std::string json);
    ~AuthMessage() override;
};


#endif //WHISPERERENGINE_AUTHMESSAGE_H
