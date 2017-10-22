//
// Created by Sam on 9/25/2017.
//

#include "../../include/Game/Core/Game.h"
#include "../../include/Game/Core/Player.h"
#include "../../include/Network/Server.h"

#include <iostream>
#include <boost/bind/bind.hpp>


typedef boost::shared_ptr<Client> pointer;


pointer Client::Create(boost::asio::io_service & ioService)
{
    return pointer(new Client(ioService));
}

boost::asio::ip::tcp::socket & Client::GetSocket()
{
    return socket;
}

void Client::Start(Server* server)
{
    this->server = server;
    Write("Connected!");

    boost::asio::async_read_until(socket, buffer, delimiter,
                                  boost::bind(&Client::Listen, shared_from_this(),
                                              boost::asio::placeholders::error));

    std::cout << "Listening for messages from client..." << std::endl;
}

void Client::Write(std::string data)
{
    data.append(delimiter);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
                             boost::bind(&Client::OnWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Client::Disconnect()
{
    socket.close();
    std::cout << "Lost connection to client!" << std::endl;
}

void Client::Listen()
{
    std::cout << "Message from " << static_cast<void*>(this) << ": " << GetString(buffer) << std::endl;

    boost::asio::async_read_until(socket, buffer, delimiter,
                                  boost::bind(&Client::Listen, shared_from_this(),
                                              boost::asio::placeholders::error));
}

std::string Client::GetString(boost::asio::streambuf& buffer)
{
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string data(
            boost::asio::buffers_begin(bufs),
            boost::asio::buffers_begin(bufs) + buffer.size());

    // Return everything except the last character delimeter
    return data.substr(0, data.size() - 1);
}

void Client::OnWrite(const boost::system::error_code & errorCode, size_t bytesTransferred) const
{
}

Client::Client(boost::asio::io_service & ioService)
        : player(nullptr), server(nullptr), listening(false), socket(ioService)
{
}
