
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Army.h"
#include "Network.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 800), "Chess");
    Network network;
    Army army(false);

    //network.createConnection("127.0.0.1", 4109);

    //network.sendMessage("Wow!");
    //std::string tmp = network.receiveMassage();
    //std::cout << tmp << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        army.game(&window, 1);

        window.clear();
        army.draw(&window);
        window.display();
    }

    return 0;
}