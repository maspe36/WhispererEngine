//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_SERVER_H
#define WHISPERERENGINE_SERVER_H


#include <queue>
#include "Client.h"

class Player;

class Server
{
public:
    std::vector<Client::pointer> clients;
    std::queue<Player*> queue;

    void WriteToAll(std::string data);
    Server(boost::asio::io_service& ioService, int port);

private:
    boost::asio::ip::tcp::acceptor acceptor;

    void Start();
    void OnAccept(Client::pointer connection, const boost::system::error_code& error);

    static void Close(Client::pointer connection);
};

#endif //WHISPERERENGINE_SERVER_H
