//
// Created by Sam on 9/25/2017.
//

#include "../../include/Network/Server.h"
#include "../../include/Game/Game.h"
#include "../../include/Game/Player.h"
#include "../../include/Network/Message.h"

void Server::writeAll(std::string data)
{
    for (const auto &i : clients)
    {
        i->write(data);
    }

    std::cout << data << std::endl;
}

void Server::start()
{
    // Is the io_thread or matchmaking_thread already running?
    if (io_thread && matchmaking_thread)
    {
        return;
    }

    std::cout << "Starting server..." << std::endl;

    listen();

    io_thread.reset(new boost::thread(
            boost::bind(&boost::asio::io_service::run, &io_service)
    ));

    matchmaking_thread.reset(new boost::thread(
            boost::bind(&Server::matchMake, shared_from_this(), std::ref(quit))
    ));

    std::cout << "Server started!" << std::endl;
}

void Server::stop()
{
    // Is the io_thread already stopped
    if (!io_thread && !matchmaking_thread)
    {
        return;
    }

    // Stop and join the io_thread and matchmaking_thread
    io_service.stop();
    io_thread->join();
    quit = true;
    matchmaking_thread->join();

    io_service.reset();
    io_thread.reset();
    matchmaking_thread.reset();
}

void Server::addClient(Client::pointer client)
{
    clients.push_back(client);
    std::cout << "'" << client->name << "' has connected from " << client->getAddress() << "!" << std::endl;
}

void Server::removeClient(Client::pointer client)
{
    // Close the connection
    close(client);

    // Remove this client from the list of active clients
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

    // Remove this clients player pointer from the queue
    queue.erase(std::remove(queue.begin(), queue.end(), client->player), queue.end());
}

void Server::endGame(std::shared_ptr<Game> game)
{

    std::cout << "Game over between ";
    for (const auto& player : game->players)
    {
        if (player != game->players.back())
        {
            std::cout << player->name;
        }
        else
        {
            std::cout << " and " << player->name << std::endl;
        }
    }

    // Reset the callback listeners to listen for the lobby function
    resetPlayerClientListeners(game);
    games.erase(std::remove(games.begin(), games.end(), game), games.end());
}

void Server::resetPlayerClientListeners(const std::shared_ptr<Game> &game) const
{
    for (const auto& player : game->players)
    {
        player->client->resetLobbyListen();
    }
}

Server::Server(int port)
        : database(Database()), factory(Factory()), io_service(), workLock(io_service), io_thread(),
          matchmaking_thread(), acceptor(io_service,
                                         boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                                        static_cast<unsigned short>(port))),
          quit(false)
{
    std::cout << "Initializing server..." << std::endl;
}

void Server::listen()
{
    Client::pointer client = Client::create(acceptor.get_io_service());

    // Calls onAccept when a connection happens
    acceptor.async_accept(client->getSocket(),
                          boost::bind(&Server::onAccept, this, client,
                                      boost::asio::placeholders::error));
}

void Server::matchMake(std::atomic<bool>& quit)
{
    while(!quit)
    {
        if (queue.size() >= 2)
        {
            std::vector<std::shared_ptr<Player>> players;

            while(players.size() < 2)
            {
                std::shared_ptr<Player> player = queue.front();
                queue.pop_front();
                players.push_back(player);
            }

            factory.refreshCards();

            std::shared_ptr<Game> game = std::make_shared<Game>(players, shared_from_this());
            game->registerPlayers();
            game->startGame();

            std::cout << "Game started for ";
            for (const auto& player : game->players)
            {
                if (player != game->players.back())
                {
                    std::cout << player->name;
                }
                else
                {
                    std::cout << " and " << player->name << std::endl;
                }
            }

            games.push_back(game);
        }
    }
}

void Server::onAccept(Client::pointer client, const boost::system::error_code &error)
{
    if (!error)
    {
        std::cout << "Connection from " << client->getAddress() << std::endl;
        factory.refreshCards();
        client->start(shared_from_this());
    }

    // pesudo recursive
    listen();
}

void Server::close(Client::pointer client)
{
    std::cout << "Closing connection from " << client->name << std::endl;
    client->getSocket().close();
}
