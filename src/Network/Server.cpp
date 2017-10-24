//
// Created by Sam on 9/25/2017.
//

#include "../../include/Network/Server.h"
#include <iostream>
#include <boost/bind/bind.hpp>

void Server::WriteAll(std::string data)
{
    for (const auto &i : clients)
    {
        i->Write(data);
    }

    std::cout << data << std::endl;
}

void Server::Start()
{
    // Is the thread already running
    if (thread)
    {
        return;
    }

    // Reset the thread
    thread.reset(new boost::thread(
            boost::bind(&boost::asio::io_service::run, &io_service)
    ));
}

void Server::Stop()
{
    // Is the thread already stopped
    if (!thread)
    {
        return;
    }

    // Stop and join the thread
    io_service.stop();
    thread->join();
    io_service.reset();
    thread.reset();
}

Server::Server(int port)
        : io_service(), workLock(io_service), thread(),
          acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                              static_cast<unsigned short>(port)))
{
    std::cout << "Listening for clients..." << std::endl;
    Listen();
}

void Server::Listen()
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
        clients.push_back(newClient);
        newClient->Start(this);
        std::cout << "Client connected!" << std::endl;
    }
    // pesudo recursive
    Listen();
}

void Server::Close(Client::pointer connection)
{
    std::cout << "Lost connection to client!" << std::endl;
    connection->GetSocket().close();
}
