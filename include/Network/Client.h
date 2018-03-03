//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CLIENT_H
#define WHISPERERENGINE_CLIENT_H


#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "Message.h"

class Player;
class Server;
class Card;

class Client
        : public std::enable_shared_from_this<Client>
{
public:
    typedef std::shared_ptr<Client> pointer;
    typedef void (Client::*clientFunc)();
    typedef void (Client::*clientProtocolFunc)(const Message& message);
    typedef void (Player::*playerProtocolFunc)(const Message& message);
    typedef std::map<std::string, clientProtocolFunc> clientFunctionMap;
    typedef std::map<std::string, playerProtocolFunc> playerFunctionMap;

    std::string name;
    std::string steamID;
    std::shared_ptr<Player> player;
    std::shared_ptr<Server> server;
    clientFunctionMap clientProtocol;
    playerFunctionMap playerProtocol;
    bool listening;

    static pointer create(boost::asio::io_service &ioService);
    boost::asio::ip::tcp::socket& getSocket();
    std::string getAddress();

    void start(std::shared_ptr<Server> server);
    void write(std::string data);
    void disconnect();
    void asyncListen(clientFunc callback);
    void listen(const boost::system::error_code &errorCode, clientFunc callback);

    void handleQueue(const Message& message);
    void handleLogin(const Message& message);

private:
    std::string delimiter;
    boost::asio::streambuf buffer;
    boost::asio::ip::tcp::socket socket;

    std::string getString(boost::asio::streambuf &buffer);
    void emptyBuffer();
    void onWrite(const boost::system::error_code &error, size_t bytesTransferred) const;

    void assembleDeck(const std::string& deckID);

    void assembleProtocolMap();
    void protocolListen();
    bool searchMap(Message& message, std::map map);

    explicit Client(boost::asio::io_service& ioService);
};


#endif //WHISPERERENGINE_CLIENT_H
