#include "Board.h"

Board::Board()
{
	m_shape = new sf::RectangleShape * [8];
	for (int i = 0; i < 8; i++)
		m_shape[i] = new sf::RectangleShape[8];

	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			m_shape[j][i].setSize(sf::Vector2f(80.f, 80.f));
			m_shape[j][i].setOrigin(sf::Vector2f(40.f, 40.f));
			m_shape[j][i].setPosition(sf::Vector2f((i * 80) + 50, (j * 80) + 50));
			if ((i + j) % 2 == 0)
				m_shape[j][i].setFillColor(sf::Color(200, 200, 200));
			else
				m_shape[j][i].setFillColor(sf::Color(60, 60, 60));

			std::cout << m_shape[j][i].getPosition().x << " " << m_shape[j][i].getPosition().y << " ";
		}
		std::cout << std::endl;
	}
}

void Board::display(sf::RenderWindow* window)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			window->draw(m_shape[j][i]);
}

sf::RectangleShape** Board::getBoard()
{
	return m_shape;
}
