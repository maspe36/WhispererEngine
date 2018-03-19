//
// Created by Sam on 1/15/2018.
//

#include "../../include/Network/Client.h"
#include "../../include/Network/Message.h"
#include "../../include/Network/Exceptions/JSONError.h"
#include <utility>


std::string Message::SUCCESS = "success";
std::string Message::FAILURE = "failure";
std::string Message::LOGIN = "login";
std::string Message::QUEUE = "queue";
std::string Message::REGISTER_PLAYER = "registerPlayer";
std::string Message::START_GAME = "startGame";
std::string Message::PLAY_CARD = "playCard";
std::string Message::CARD_MOVED = "cardMoved";
std::string Message::START_TURN = "startTurn";
std::string Message::END_TURN = "endTurn";
std::string Message::STOP_TURN = "stopTurn";
std::string Message::FIGHT_PLAYER = "fightPlayer";

std::string Message::CHAT = "chat";

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

void Message::loadJSON(const nlohmann::json& newJSON)
{
    rawJSON = newJSON;
}

void Message::addDataMember(std::string key, json value)
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
    if (json::accept(cause))
    {
        message.addDataMember("cause", json::parse(cause));
    }
    else
    {
        message.addDataMember("cause", std::move(cause));
    }

    return message.getJSON();
}

const std::string Message::login()
{
    return Message(LOGIN).getJSON();
}

const std::string Message::registerPlayer(const json& deckJSON, std::shared_ptr<Client> client)
{
    Message message(REGISTER_PLAYER);
    message.addDataMember("decks", deckJSON);
    message.addDataMember("name", client->name);
    message.addDataMember("avatarURL", client->avatarURL);
    return message.getJSON();
}
