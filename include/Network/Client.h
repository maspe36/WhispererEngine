//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CLIENT_H
#define WHISPERERENGINE_CLIENT_H


#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

class Player;
class Server;
class Card;

class Client
        : public std::enable_shared_from_this<Client>
{
public:
    typedef std::shared_ptr<Client> pointer;
    typedef void (Client::*clientFunc)();

    std::string name;
    std::string steamID;
    std::shared_ptr<Player> player;
    std::shared_ptr<Server> server;
    bool listening;

    static pointer Create(boost::asio::io_service& ioService);
    boost::asio::ip::tcp::socket& GetSocket();
    std::string GetAddress();

    void Start(std::shared_ptr<Server> server);
    void Write(std::string data);
    void Disconnect();
    void AsyncListen(clientFunc callback);
    void Listen(const boost::system::error_code& errorCode, clientFunc callback);

private:
    std::string delimiter;
    boost::asio::streambuf buffer;
    boost::asio::ip::tcp::socket socket;

    std::string getString(boost::asio::streambuf &buffer);
    void emptyBuffer();
    void authenticationHandler();
    void serverHandler();
    void gameHandler();

    void handleQueue(std::string data);
    void assembleDeck(const std::string& deckID);

    void OnWrite(const boost::system::error_code& error, size_t bytesTransferred) const;

    explicit Client(boost::asio::io_service& ioService);
};


#endif //WHISPERERENGINE_CLIENT_H
