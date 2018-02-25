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
#include "../../include/Network/Exceptions/JSONError.h"

#include <iostream>
#include <utility>
#include <curl/curl.h>
#include <pybind11/pytypes.h>

typedef boost::shared_ptr<Client> pointer;


pointer Client::Create(boost::asio::io_service & ioService)
{
    return pointer(new Client(ioService));
}

boost::asio::ip::tcp::socket & Client::GetSocket()
{
    return socket;
}

std::string Client::GetAddress()
{
    return shared_from_this()->GetSocket().remote_endpoint().address().to_string();
}

void Client::Start(Server* server)
{
    this->server = server;
    Write(Message::success());

    listening = true;
    Write(Message::auth());
    AsyncListen(&Client::authenticationHandler);
}

void Client::Write(std::string data)
{
    data.append(delimiter);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
                             boost::bind(&Client::OnWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Client::Disconnect()
{
    socket.close();
    server->RemoveClient(shared_from_this());
    std::cout << "Lost connection to client!" << std::endl;
}

void Client::AsyncListen(clientFunc callback)
{
    boost::asio::async_read_until(socket, buffer, delimiter,
                                  boost::bind(&Client::Listen, shared_from_this(),
                                              boost::asio::placeholders::error, callback));
}

void Client::Listen(const boost::system::error_code& errorCode, clientFunc callback)
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
            Write(Message::fail(error.what()));
            (*this.*callback)();
        }
    }
    else
    {
        Disconnect();
    }
}

size_t Client::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Client::makeGETRequest(std::string url)
{
    CURL *curl;
    CURLcode result;
    std::string readBuffer;

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            std::cerr << (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result)) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
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

    // HTTP Request with the token to get steamID
    // Verify response

//        name = httpRequest.name;
//        clientID = httpRequest.clientID;

    server->AddClient(shared_from_this());
    Write(Message::success());

    AsyncListen(&Client::serverHandler);
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

    AsyncListen(&Client::serverHandler);
}

void Client::gameHandler()
{
    std::string data = getString(buffer);
    std::cout << "From " << name << ": " << data << std::endl;

    AsyncListen(&Client::gameHandler);
}

void Client::handleQueue(std::string data)
{
    QueueMessage qMessage(std::move(data));
    assemblePlayer();
    assembleDeck(qMessage.deckID);
}

void Client::assemblePlayer()
{
    player = new Player(shared_from_this());
}

void Client::assembleDeck(std::string deckID)
{
    std::vector<std::string> pythonNames = server->database.getDeckCards(clientID, std::move(deckID));
    std::vector<std::shared_ptr<Card>> deck;

    for (const auto &name : pythonNames)
    {
        auto card = server->factory.createCard(name);
        deck.push_back(card);
    }

    player->board->deck = deck;
}

void Client::OnWrite(const boost::system::error_code & errorCode, size_t bytesTransferred) const
{
}

Client::Client(boost::asio::io_service & ioService)
        : player(nullptr), server(nullptr), listening(false), socket(ioService), delimiter("\n")
{
}
