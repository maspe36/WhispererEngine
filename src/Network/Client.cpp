//
// Created by Sam on 9/25/2017.
//

#include "../../include/Game/Core/Board.h"
#include "../../include/Game/Core/Card.h"
#include "../../include/Game/Core/Game.h"
#include "../../include/Game/Core/Player.h"
#include "../../include/Network/Client.h"
#include "../../include/Network/HTTPRequest.h"
#include "../../include/Network/Message.h"
#include "../../include/Network/Server.h"
#include "../../include/Network/Derived/AuthMessage.h"
#include "../../include/Network/Derived/QueueMessage.h"

#include <iostream>
#include <utility>
#include <pybind11/pytypes.h>


Client::pointer Client::create(boost::asio::io_service &ioService)
{
    return pointer(new Client(ioService));
}

boost::asio::ip::tcp::socket & Client::getSocket()
{
    return socket;
}

std::string Client::getAddress()
{
    return shared_from_this()->getSocket().remote_endpoint().address().to_string();
}

void Client::start(std::shared_ptr<Server> server)
{
    this->server = std::move(server);
    write(Message::success());

    listening = true;
    write(Message::login());
    asyncListen(&Client::protocolListen);
}

void Client::write(std::string data)
{
    data.append(delimiter);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
                             boost::bind(&Client::onWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Client::disconnect()
{
    socket.close();
    server->removeClient(shared_from_this());
    std::cout << "Lost connection to client!" << std::endl;
}

void Client::asyncListen(clientFunc callback)
{
    boost::asio::async_read_until(socket, buffer, delimiter,
                                  boost::bind(&Client::listen, shared_from_this(),
                                              boost::asio::placeholders::error, callback));
}

void Client::listen(const boost::system::error_code &errorCode, clientFunc callback)
{
    if (errorCode == nullptr && listening)
    {
        try
        {
            (*this.*callback)();
        }
        catch(const std::exception &error)
        {
            std::cout << "Error during callback: " << error.what() << std::endl;
            write(Message::fail(error.what()));
            asyncListen(callback);
        }
    }
    else
    {
        disconnect();
    }
}

void Client::handleQueue(const json& rawJSON)
{
    QueueMessage qMessage(rawJSON);

    player = std::make_shared<Player>(shared_from_this());
    assembleDeck(qMessage.deckID);

    server->queue.push_back(player);
    std::cout << "Queue | Name: " << player->name << " deckID: " << qMessage.deckID << std::endl;
}

void Client::handleLogin(const json& rawJSON)
{
    AuthMessage authMessage(rawJSON);

    steamID = HTTPRequest::getSteamID(authMessage.token);
    name = HTTPRequest::getSteamName(steamID);

    server->addClient(shared_from_this());

    json deckJSON = createRegisterPlayerJSON();
    write(Message::registerPlayer(deckJSON));
}

std::vector<json> Client::createRegisterPlayerJSON() const
{
    std::vector<json> deckJSON;

    std::map<std::string, Deck> deckMap = server->database.getAllDeckCards(steamID, &server->factory);

    for (const auto& deckInfo : deckMap)
    {
        Deck deck = deckInfo.second;
        deckJSON.push_back(deck.getJSON());
    }

    return deckJSON;
}

std::string Client::getString(boost::asio::streambuf &buffer)
{
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string data(
            boost::asio::buffers_begin(bufs),
            boost::asio::buffers_begin(bufs) + buffer.size());

    emptyBuffer();

    // Return everything except the last character delimeter
    return data.substr(0, data.size() - 1);
}

void Client::emptyBuffer()
{
    buffer.consume(buffer.size());
}

void Client::onWrite(const boost::system::error_code &errorCode, size_t bytesTransferred) const
{
}

void Client::assembleDeck(const std::string& deckID)
{
    std::vector<std::string> pythonNames = server->database.getDeckCards(steamID, deckID);

    std::vector<std::shared_ptr<Card>> cards;
    for (const auto &pythonName : pythonNames)
    {
        auto card = server->factory.createCard(pythonName);
        card->player = player;
        cards.push_back(card);
    }

    player->board->deck = std::make_shared<Deck>(deckID, cards);
}

void Client::assembleProtocolMap()
{
    clientProtocol[Message::LOGIN] = &Client::handleLogin;
    clientProtocol[Message::QUEUE] = &Client::handleQueue;
    playerProtocol[Message::SEND_CHAT] = &Player::sendChatMessage;
    playerProtocol[Message::PLAY_CARD] = &Player::playCard;
}

void Client::protocolListen()
{
    std::string data = getString(buffer);
    auto rawJSON = json::parse(data);
    std::string type = rawJSON[Message::TYPE_KEY];

    auto clientIter = clientProtocol.find(type);
    bool clientCallable = !(clientIter == clientProtocol.end());

    auto playerIter = playerProtocol.find(type);
    bool playerCallable = !(playerIter == playerProtocol.end());

    if (clientCallable)
    {
        ((*this).*clientProtocol[type])(rawJSON);
    }
    else if (playerCallable)
    {
        ((*player).*playerProtocol[type])(rawJSON);
    }
    else
    {
        write(Message::fail("Unknown protocol '" + type + "'"));
    }

    asyncListen(&Client::protocolListen);
}

Client::Client(boost::asio::io_service & ioService)
        : player(nullptr), server(nullptr), listening(false), socket(ioService), delimiter("\n")
{
    assembleProtocolMap();
}
