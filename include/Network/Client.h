//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CLIENT_H
#define WHISPERERENGINE_CLIENT_H


#include <memory>
#include <vector>
#include <boost/asio.hpp>
#include <boost/variant.hpp>
#include <boost/bind/bind.hpp>
#include "Message.h"
#include "../Game/Core/Player.h"

class Server;
class Card;

class Client
        : public std::enable_shared_from_this<Client>
{
public:
    typedef std::shared_ptr<Client> pointer;
    typedef void (Client::*func)();
    typedef void (Client::*protocolFunc)(const json& rawJSON);
    typedef std::map<std::string, protocolFunc> LobbyFunctions;
    typedef std::map<std::string, Player::protocolFunc> GameFunctions;

    std::string name;
    std::string steamID;
    std::shared_ptr<Player> player;
    std::shared_ptr<Server> server;

    LobbyFunctions lobbyFunctions;
    GameFunctions gameFunctions;
    func listenerCallback;
    bool listening;

    static pointer create(boost::asio::io_service &ioService);
    boost::asio::ip::tcp::socket& getSocket();
    std::string getAddress();

    void start(std::shared_ptr<Server> server);
    void write(std::string data);
    void disconnect();
    void asyncListen(func callback);
    void listen(const boost::system::error_code &errorCode, func callback);

    void handleQueue(const json& rawJSON);
    void handleLogin(const json& rawJSON);

private:
    std::string delimiter;
    boost::asio::streambuf buffer;
    boost::asio::ip::tcp::socket socket;

    std::string getString(boost::asio::streambuf &buffer);
    void emptyBuffer();
    void onWrite(const boost::system::error_code &error, size_t bytesTransferred) const;

    void assembleDeck(const std::string& deckID);

    void assembleProtocolMap();
    void lobbyListen();
    void gameListen();

    explicit Client(boost::asio::io_service& ioService);

    std::vector<json> createRegisterPlayerJSON() const;
};


#endif //WHISPERERENGINE_CLIENT_H
