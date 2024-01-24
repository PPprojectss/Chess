
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <sstream>

#include "Army.h"
#include "Network.h"

struct Server
{
    bool turn;
    bool turnEnded;
    bool endGame;
    int piece;
    float x;
    float y;
};

Server* server;

void ManageConnection(Network* network)
{
    while(server->endGame != true)
    { 
        std::cout << "Czekam" << std::endl;
        while (server->turn == true);
        std::cout << "Czekam na dane" << std::endl;

        std::string foo = network->receiveMassage();

        if (foo == "END")
        {
            server->endGame = true;
            return;
        }

        std::stringstream test(foo);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(test, segment, ' '))
        {
            seglist.push_back(segment);
        }

        std::cout << seglist[0] << " " << seglist[1] << " " << seglist[2] << std::endl;
        std::cout << strtol(seglist[0].c_str(), NULL, 0) << " " << strtol(seglist[1].c_str(), NULL, 0) << " " << strtol(seglist[2].c_str(), NULL, 0) << std::endl;

        server->piece = strtol(seglist[0].c_str(), NULL, 0);
        float xx, yy;
        xx = strtol(seglist[1].c_str(), NULL, 0);
        yy = strtol(seglist[2].c_str(), NULL, 0);

        yy = 660 - yy;
        xx = 660 - xx;

        server->x = xx;
        server->y = yy;
        
        server->turn = true;
        server->turnEnded = true;
    }

}

int main()
{
    std::string ip;
    short port;
    std::string choice;

    short status = 0;

    Army* army = nullptr;
    server = new Server;

    server->turn = false;
    server->turnEnded = false;


    std::cout << "Witaj w grze Szachy !!!!" << std::endl;
    std::cout << "Podaj adres IP: ";
    std::cin >> ip;
    std::cout << "Podaj port: ";
    std::cin >> port;

    Network network;
    network.createConnection(ip, port);

    do
    {
        std::cout << "Co chesz zrobic?" << std::endl;
        std::cout << "(1 - utworz pokoj)" << std::endl;
        std::cout << "(2 - dolacz do pokoju)" << std::endl;
        std::cin >> choice;

        if (choice[0] == '1')
        {
            network.sendMessage("C");

            std::string tmp = network.receiveMassage();

            std::cout << "Created room: " << tmp << std::endl;
        }
        if (choice[0] == '2')
        {
            std::string roomChoice;
            std::string mess;
            mess.append("J ");
            std::cout << "Enter room to join: ";
            std::cin >> roomChoice;
            mess.append(roomChoice);

            network.sendMessage(mess);
        }



        std::string tmp = network.receiveMassage();

        std::cout << tmp << std::endl;

        if (tmp[0] == 'S')
        {
            if (tmp[6] == 'W')
            {
                army = new Army(true);
                status = 1;
                std::cout << tmp[6] << "  Grasz jako biale" << std::endl;
                server->turn = true;
            }
            else if (tmp[6] == 'B')
            {
                army = new Army(false);
                status = 2;
                std::cout << tmp[6] << "  Grasz jako czarne" << std::endl;
            }
        }

    } while (status == 0);

    std::thread worker(ManageConnection, &network);

    sf::RenderWindow window(sf::VideoMode(660, 660), "Chess");

    while (window.isOpen())
    {
        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (server->endGame == true)
        {
            return -1;
        }

        if (server->turnEnded == true and server->turn == true)
        {
            army->updatePiece(server->piece, sf::Vector2f(server->x, server->y));
            server->turnEnded = false;
        }

        if(server->turn == true)
        {
            std::string tmp = army->game(&window);

            if (tmp != "")
            {
                network.sendMessage(tmp);
                server->turnEnded = true;
                server->turn = false;
            }
        }

        window.clear();
        army->draw(&window);
        army->drawPossibleMoves(&window);
        window.display();
    }

    server->endGame = true;
    network.~Network();

    std::cin;
    std::cin;

    return 0;
}