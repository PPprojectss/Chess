#include "Army.h"

Army::Army(bool white) // 8 9 10 11 12 13 14 15
{
	m_selected = 16; 
	m_mousePressed = false;

	if (white)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_piece[i].loadTexture("PawnW", sf::Vector2f(float(50 + (i * 80)), 530));
			if (i == 8 or i == 15)
				m_piece[i].loadTexture("TowerW", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 9 or i == 14)
				m_piece[i].loadTexture("HorseW", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 10 or i == 13)
				m_piece[i].loadTexture("BishopW", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 11)
				m_piece[i].loadTexture("QueenW", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 12)
				m_piece[i].loadTexture("KingW", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
		}

		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_pieceE[i].loadTexture("PawnB", sf::Vector2f(float(50 + (i * 80)), 130));
			if (i == 8 or i == 15)
				m_pieceE[i].loadTexture("TowerB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 9 or i == 14)
				m_pieceE[i].loadTexture("HorseB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 10 or i == 13)
				m_pieceE[i].loadTexture("BishopB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 11)
				m_pieceE[i].loadTexture("QueenB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 12)
				m_pieceE[i].loadTexture("KingB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
		}

	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_piece[i].loadTexture("PawnB", sf::Vector2f(float(50 + (i * 80)), 530));
			if (i == 8 or i == 15)
				m_piece[i].loadTexture("TowerB", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 9 or i == 14)
				m_piece[i].loadTexture("HorseB", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 10 or i == 13)
				m_piece[i].loadTexture("BishopB", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 11)
				m_piece[i].loadTexture("QueenB", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
			if (i == 12)
				m_piece[i].loadTexture("KingB", sf::Vector2f(float(50 + ((i - 8) * 80)), 610));
		}

		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_pieceE[i].loadTexture("PawnW", sf::Vector2f(float(50 + (i * 80)), 130));
			if (i == 8 or i == 15)
				m_pieceE[i].loadTexture("TowerW", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 9 or i == 14)
				m_pieceE[i].loadTexture("HorseW", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 10 or i == 13)
				m_pieceE[i].loadTexture("BishopW", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 11)
				m_pieceE[i].loadTexture("QueenW", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 12)
				m_pieceE[i].loadTexture("KingW", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
		}
	}
}

void Army::draw(sf::RenderWindow* window)
{
	m_board.display(window);

	for (int i = 0; i < 16; i++)
		m_piece[i].draw(window);
	for (int i = 0; i < 16; i++)
		m_pieceE[i].draw(window);

}

void Army::game(sf::RenderWindow* window, bool turn)
{
	if (turn)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i position = sf::Mouse::getPosition(*window);

			if (m_selected == 16)
			{
				for (int i = 0; i < 16; i++)
				{
					if (m_piece[i].getShape()->getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
					{
						m_selected = i;
						std::cout << i << std::endl;
						m_mousePressed = true;
						break;
					}
				}
			}

			if (m_selected != 16)
			{
				sf::Vector2i position = sf::Mouse::getPosition(*window);

				m_piece[m_selected].getShape()->setPosition(sf::Vector2f(position.x, position.y));
			}
		}
		else if (m_mousePressed == true)
		{
			std::cout << "Koniec" << std::endl;
			m_mousePressed = false;
			; // info do serwa ze koniec ruchu
		}
		else
			m_selected = 16;

		
	}
}
