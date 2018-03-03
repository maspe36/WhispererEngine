//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_SERVER_H
#define WHISPERERENGINE_SERVER_H


#include "Client.h"
#include "../Game/Python/Factory.h"
#include "../Game/Utilities/Database.h"
#include <queue>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

class Game;
class Player;

class Server
        : public std::enable_shared_from_this<Server>
{
public:
    std::vector<std::shared_ptr<Game>> games;
    std::vector<Client::pointer> clients;
    std::queue<std::shared_ptr<Player>> queue;
    Database database;
    Factory factory;

    void writeAll(std::string data);
    void start();
    void stop();
    void addClient(Client::pointer client);
    void removeClient(Client::pointer client);

    explicit Server(int port);

private:
    boost::asio::io_service io_service;
    boost::asio::io_service::work workLock;
    boost::scoped_ptr<boost::thread> io_thread;
    boost::scoped_ptr<boost::thread> matchmaking_thread;
    boost::asio::ip::tcp::acceptor acceptor;
    std::atomic<bool> quit;

    void listen();
    void onAccept(Client::pointer client, const boost::system::error_code &error);

    void matchMake(std::atomic<bool>& quit);

    static void close(Client::pointer connection);
};

#endif //WHISPERERENGINE_SERVER_H
