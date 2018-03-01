//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_SERVER_H
#define WHISPERERENGINE_SERVER_H


#include <queue>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include "Client.h"
#include "../Game/Utilities/Database.h"
#include "../Game/Python/Factory.h"

class Player;

class Server
        : public std::enable_shared_from_this<Server>
{
public:
    std::vector<Client::pointer> clients;
    std::queue<std::shared_ptr<Player>> queue;
    Database database;
    Factory factory;

    void WriteAll(std::string data);
    void Start();
    void Stop();
    void AddClient(Client::pointer client);
    void RemoveClient(Client::pointer client);

    explicit Server(int port);

private:
    boost::asio::io_service io_service;
    boost::asio::io_service::work workLock;
    boost::scoped_ptr<boost::thread> thread;
    boost::asio::ip::tcp::acceptor acceptor;

    void Listen();
    void OnAccept(Client::pointer client, const boost::system::error_code& error);

    static void Close(Client::pointer connection);
};

#endif //WHISPERERENGINE_SERVER_H
