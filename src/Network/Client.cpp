//
// Created by Sam on 9/25/2017.
//

#include "../../include/Network/Client.h"
#include "../../include/Network/Server.h"
#include "../../include/Game/Core/Game.h"
#include "../../include/Game/Core/Player.h"
#include "../../include/Game/Core/Card.h"
#include "../../include/Network/Message.h"
#include "../../include/Network/Derived/AuthMessage.h"
#include "../../include/Network/Derived/QueueMessage.h"
#include "../../include/Game/Core/Board.h"
#include "../../include/Network/HTTPRequest.h"

#include <iostream>
#include <utility>
#include <pybind11/pytypes.h>

typedef std::shared_ptr<Client> pointer;


pointer Client::create(boost::asio::io_service &ioService)
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
    write(Message::auth());
    asyncListen(&Client::authenticationHandler);
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

void Client::authenticationHandler()
{
    std::string json = getString(buffer);

    AuthMessage authMessage(json);

    steamID = HTTPRequest::getSteamID(authMessage.token);
    name = HTTPRequest::getSteamName(steamID);

    server->addClient(shared_from_this());
    write(Message::registerPlayer());

    asyncListen(&Client::serverHandler);
}

void Client::serverHandler()
{
    std::string data = getString(buffer);
    Message message;
    message.loadJSON(data);

    std::string type = message.getType();

    if (type == Message::QUEUE)
    {
        handleQueue(data);
    }

    asyncListen(&Client::serverHandler);
}

void Client::gameHandler()
{
    std::string data = getString(buffer);
    std::cout << "From " << name << ": " << data << std::endl;

    asyncListen(&Client::gameHandler);
}

void Client::handleQueue(std::string data)
{
    QueueMessage qMessage(std::move(data));

    player = std::make_shared<Player>(shared_from_this());
    assembleDeck(qMessage.deckID);

    server->queue.push(player);
    std::cout << "Queue | Name: " << player->name << " deckID: " << qMessage.deckID << std::endl;
}

void Client::assembleDeck(const std::string& deckID)
{
    std::vector<std::string> pythonNames = server->database.getDeckCards(steamID, deckID);
    std::vector<std::shared_ptr<Card>> cards;

    for (const auto &name : pythonNames)
    {
        auto card = server->factory.createCard(name);
        card->player = player;
        cards.push_back(card);
    }

    player->board->deck = std::make_shared<Deck>(deckID, cards);
}

void Client::onWrite(const boost::system::error_code &errorCode, size_t bytesTransferred) const
{
}

Client::Client(boost::asio::io_service & ioService)
        : player(nullptr), server(nullptr), listening(false), socket(ioService), delimiter("\n")
{
}
