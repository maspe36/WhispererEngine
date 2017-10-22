//
// Created by Sam on 9/25/2017.
//

#include "../../include/Network/Server.h"
#include <iostream>
#include <boost/bind/bind.hpp>

void Server::WriteToAll(std::string data)
{
    for (const auto &i : clients)
    {
        i->Write(data);
    }

    std::cout << data << std::endl;
}

Server::Server(boost::asio::io_service & io_service, int port)
        : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                              static_cast<unsigned short>(port)))
{
    std::cout << "Listening for clients..." << std::endl;
    Start();
}

void Server::Start()
{
    Client::pointer NewClient =
            Client::Create(acceptor.get_io_service());

    // Calls OnAccept when a connection happens
    acceptor.async_accept(NewClient->GetSocket(),
                          boost::bind(&Server::OnAccept, this, NewClient,
                                      boost::asio::placeholders::error));
}

void Server::OnAccept(Client::pointer newClient, const boost::system::error_code & error)
{
    if (!error)
    {
        newClient->Start(this);
        clients.push_back(newClient);
        std::cout << "Client connected!" << std::endl;
    }
    // pesudo recursive
    Start();
}

void Server::Close(Client::pointer connection)
{
    std::cout << "Lost connection to client!" << std::endl;
    connection->GetSocket().close();
}