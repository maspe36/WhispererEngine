//
// Created by Sam on 1/15/2018.
//

#include "../../include/Network/Message.h"


void Message::buildJSON()
{
    auto& allocator = document.GetAllocator();

    Value val = getValue(type);
    document.AddMember("type", val, allocator);

    val = getValue(data);
    document.AddMember("data", val, allocator);
}

Message::Message(std::string type, std::string data)
        : type(std::move(type)), data(std::move(data))
{
    buildJSON();
}

Message::Message()
= default;

Message::~Message()
= default;
