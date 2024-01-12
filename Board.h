#pragma once
#include <SFML/Graphics.hpp>

class Board
{
	public:
		Board();
		~Board() = default;

		void display(sf::RenderWindow* window);
		sf::RectangleShape** getBoard();


	private:
		sf::RectangleShape** m_shape;

};

