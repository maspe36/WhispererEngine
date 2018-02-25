//
// Created by Sam on 1/15/2018.
//

#include "../../include/Network/Message.h"
#include "../../include/Network/Exceptions/JSONError.h"
#include <utility>


std::string Message::AUTH = "AUTH";
std::string Message::QUEUE = "QUEUE";

std::string Message::TYPE_KEY = "type";
std::string Message::DATA_KEY = "data";

std::string Message::getJSON()
{
    return rawJSON.dump();
}

void Message::loadJSON(std::string json)
{
    rawJSON = json::parse(json);
}

void Message::addDataMember(std::string key, std::string value)
{
    rawJSON[DATA_KEY][key] = value;
}

std::string Message::getType()
{
    return rawJSON[TYPE_KEY];
}

std::string Message::getMember(std::string key)
{
    return rawJSON[key];
}

std::string Message::getDataMember(std::string key)
{
    std::string result;

    try
    {
        result = rawJSON[DATA_KEY][key];
    }
    catch (const nlohmann::detail::type_error &exception)
    {
        throw JSONError("The key '" + key + "' is missing from the JSON!");
    }

    return result;
}

Message::Message(std::string type)
{
    rawJSON[TYPE_KEY] = type;
    rawJSON[DATA_KEY] = nullptr;
}

Message::Message()
{
    rawJSON[TYPE_KEY] = "";
    rawJSON[DATA_KEY] = nullptr;
}

Message::~Message()
= default;

const std::string Message::success()
{
    return Message("success").getJSON();
}

const std::string Message::fail()
{
    Message message("fail");
    message.addDataMember("cause", "Unknown error");

    return message.getJSON();
}

const std::string Message::fail(std::string cause)
{
    Message message("fail");
    message.addDataMember("cause",std::move(cause));

    return message.getJSON();
}

const std::string Message::auth()
{
    return Message("authentication").getJSON();
}
