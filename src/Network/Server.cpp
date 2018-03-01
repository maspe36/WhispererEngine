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

    std::cout << "Starting server..." << std::endl;

    Listen();

    thread.reset(new boost::thread(
            boost::bind(&boost::asio::io_service::run, &io_service)
    ));

    std::cout << "Server started!" << std::endl;
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
        : database(Database()), factory(Factory()), io_service(), workLock(io_service), thread(),
          acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                              static_cast<unsigned short>(port)))
{
    std::cout << "Initializing server..." << std::endl;
}

void Server::Listen()
{
    Client::pointer client = Client::Create(acceptor.get_io_service());

    // Calls OnAccept when a connection happens
    acceptor.async_accept(client->GetSocket(),
                          boost::bind(&Server::OnAccept, this, client,
                                      boost::asio::placeholders::error));
}

void Server::OnAccept(Client::pointer client, const boost::system::error_code & error)
{
    if (!error)
    {
        std::cout << "Connection from " << client->GetAddress() << std::endl;
        client->Start(shared_from_this());
    }

    // pesudo recursive
    Listen();
}

void Server::Close(Client::pointer client)
{
    std::cout << "Closing connection from " << client->name << std::endl;
    client->GetSocket().close();
}

void Server::AddClient(Client::pointer client)
{
    clients.push_back(client);
    std::cout << "'" << client->name << "' has connected from " << client->GetAddress() << "!" << std::endl;
}

void Server::RemoveClient(Client::pointer client)
{
    Close(client);
    auto newEnd = std::remove(clients.begin(), clients.end(), client);
    clients.erase(newEnd, clients.end());
}
