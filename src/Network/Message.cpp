//
// Created by Sam on 1/15/2018.
//

#include "../../include/Network/Message.h"
#include "../../include/Network/Exceptions/JSONError.h"
#include <utility>


std::string Message::SUCCESS = "success";
std::string Message::FAILURE = "failure";
std::string Message::AUTH = "auth";
std::string Message::QUEUE = "queue";
std::string Message::REGISTER_PLAYER = "registerPlayer";

std::string Message::TYPE_KEY = "type";
std::string Message::DATA_KEY = "data";

std::string Message::getJSON()
{
    return rawJSON.dump();
}

void Message::loadJSON(std::string json)
{
    try
    {
        rawJSON = json::parse(json);
    }
    catch (const nlohmann::detail::type_error &exception)
    {
        throw JSONError("The message '" + json + "' is invalid and cannot be parsed");
    }
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
    return Message(SUCCESS).getJSON();
}

const std::string Message::fail(std::string cause)
{
    Message message(FAILURE);
    message.addDataMember("cause",std::move(cause));

    return message.getJSON();
}

const std::string Message::auth()
{
    return Message(AUTH).getJSON();
}

const std::string Message::registerPlayer()
{
    return Message(REGISTER_PLAYER).getJSON();
}
