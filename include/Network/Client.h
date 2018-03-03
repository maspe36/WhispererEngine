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

    static pointer create(boost::asio::io_service &ioService);
    boost::asio::ip::tcp::socket& getSocket();
    std::string getAddress();

    void start(std::shared_ptr<Server> server);
    void write(std::string data);
    void disconnect();
    void asyncListen(clientFunc callback);
    void listen(const boost::system::error_code &errorCode, clientFunc callback);

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

    void onWrite(const boost::system::error_code &error, size_t bytesTransferred) const;

    explicit Client(boost::asio::io_service& ioService);
};


#endif //WHISPERERENGINE_CLIENT_H
