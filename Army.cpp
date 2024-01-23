#include "Army.h"

Army::Army(bool white) // 8 9 10 11 12 13 14 15
{
	m_selected = 16; 
	m_mousePressed = false;
	m_white = white;

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
			if (i == 12)
				m_pieceE[i].loadTexture("QueenB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
			if (i == 11)
				m_pieceE[i].loadTexture("KingB", sf::Vector2f(float(50 + ((i - 8) * 80)), 50));
		}

	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_piece[i].loadTexture("PawnB", sf::Vector2f(float(610 - (i * 80)), 530));
			if (i == 8 or i == 15)
				m_piece[i].loadTexture("TowerB", sf::Vector2f(float(610 - ((i - 8) * 80)), 610));
			if (i == 9 or i == 14)
				m_piece[i].loadTexture("HorseB", sf::Vector2f(float(610 - ((i - 8) * 80)), 610));
			if (i == 10 or i == 13)
				m_piece[i].loadTexture("BishopB", sf::Vector2f(float(610 - ((i - 8) * 80)), 610));
			if (i == 12)
				m_piece[i].loadTexture("QueenB", sf::Vector2f(float(610 - ((i - 8) * 80)), 610));
			if (i == 11)
				m_piece[i].loadTexture("KingB", sf::Vector2f(float(610 - ((i - 8) * 80)), 610));
		}

		for (int i = 0; i < 16; i++)
		{
			if (i < 8)
				m_pieceE[i].loadTexture("PawnW", sf::Vector2f(float(610 - (i * 80)), 130));
			if (i == 8 or i == 15)
				m_pieceE[i].loadTexture("TowerW", sf::Vector2f(float(610 - ((i - 8) * 80)), 50));
			if (i == 9 or i == 14)
				m_pieceE[i].loadTexture("HorseW", sf::Vector2f(float(610 - ((i - 8) * 80)), 50));
			if (i == 10 or i == 13)
				m_pieceE[i].loadTexture("BishopW", sf::Vector2f(float(610 - ((i - 8) * 80)), 50));
			if (i == 11)
				m_pieceE[i].loadTexture("QueenW", sf::Vector2f(float(610 - ((i - 8) * 80)), 50));
			if (i == 12)
				m_pieceE[i].loadTexture("KingW", sf::Vector2f(float(610 - ((i - 8) * 80)), 50));
		}
	}
}

void Army::draw(sf::RenderWindow* window)
{
	m_board.display(window);

	for (int i = 0; i < 16; i++)
		if(m_pieceE[i].dead() == false)
			m_pieceE[i].draw(window);

	for (int i = 0; i < 16; i++)
		if (m_piece[i].dead() == false)
			m_piece[i].draw(window);
}

std::string Army::game(sf::RenderWindow* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(*window);

		if (m_selected == 16)
		{
			for (int i = 0; i < 16; i++)
			{
				if (m_piece[i].getShape()->getGlobalBounds().contains(sf::Vector2f(position.x, position.y)) and m_piece[i].dead() == false)
				{
					m_selected = i;
					std::cout << i << std::endl;
					m_mousePressed = true;

					updatePossibleMoves(window);
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
		sf::Vector2i position = sf::Mouse::getPosition(*window);

		for (int i = 0; i < m_possibleMoves.size(); i++)
		{
			if(m_possibleMoves[i].getGlobalBounds().contains(sf::Vector2f(position.x, position.y)))
			{
				m_piece[m_selected].setPos(m_possibleMoves[i].getPosition());
				m_valid = true;
			}
		}

		m_possibleMoves.clear();

		if (m_valid != true)
		{
			std::cout << "Koniec, invalid move" << std::endl;

			m_piece[m_selected].reset();
			m_mousePressed = false;
			m_selected = 16;
		}

		if (m_valid == true)
		{
			std::cout << "Koniec, zadtwierdzono ruch" << std::endl;

			for (int i = 0; i < 16; i++)
			{
				if (m_pieceE[i].getPos() == m_piece[m_selected].getPos())
				{
					if (m_pieceE[i].getType() == 'K')
						return "END";
					m_pieceE[i].die();
					break;
				}
			}

			std::string mes = std::to_string(m_selected);
			mes.append(" ");
			mes.append(std::to_string(m_piece[m_selected].getShape()->getPosition().x));
			mes.append(" ");
			mes.append(std::to_string(m_piece[m_selected].getShape()->getPosition().y));

			m_selected = 16;
			m_mousePressed = false;
			m_valid = false;
			return mes;
		}
	}
	else
		m_selected = 16;

	return "";
}

void Army::updatePiece(int id, sf::Vector2f pos)
{
	m_pieceE[id].setPos(pos);

	for (int i = 0; i < 16; i++)
	{
		if (pos == m_piece[i].getPos())
		{
			std::cout << m_piece[i].getType() << " - " << i << " - zbito twoja figure" << std::endl;
			m_piece[i].die();
			break;
		}
	}
}

void Army::updatePossibleMoves(sf::RenderWindow* window)
{
	sf::Vector2f right(80, 0);
	sf::Vector2f up(0, -80);
	sf::Vector2f down(0, 80);
	sf::Vector2f left(-80, 0);


	sf::RectangleShape m_shape;

	m_shape.setSize(sf::Vector2f(80.f, 80.f));
	m_shape.setOrigin(sf::Vector2f(40.f, 40.f));
	m_shape.setFillColor(sf::Color(0, 255, 0, 100));

	if (m_piece[m_selected].getType() == 'P')
	{
		bool can_move = true;

		for (int i = 0; i < 16; i++)
		{
			if (m_pieceE[i].getPos() == m_piece[m_selected].getPos() + up or (m_piece[m_selected].getPos() + up).y < 0 )
				can_move = false;

			if (m_pieceE[i].getPos() == m_piece[m_selected].getPos() + up + left)
			{
				m_shape.setPosition(m_piece[m_selected].getPos() + up + left);
				m_possibleMoves.push_back(m_shape);

			}
			if (m_pieceE[i].getPos() == m_piece[m_selected].getPos() + up + right)
			{
				m_shape.setPosition(m_piece[m_selected].getPos() + up + right);
				m_possibleMoves.push_back(m_shape);

			}
		}

		if (can_move == true)
		{
			if (m_piece[m_selected].firstMove() == true)
			{
				m_shape.setPosition(m_piece[m_selected].getPos() + up);
				m_possibleMoves.push_back(m_shape);
				m_shape.setPosition(m_piece[m_selected].getPos() + up + up);
				m_possibleMoves.push_back(m_shape);
			}
			else
			{
				m_shape.setPosition(m_piece[m_selected].getPos() + up);
				m_possibleMoves.push_back(m_shape);
			}
		}
	}

	else if (m_piece[m_selected].getType() == 'T')
	{
		int x = m_piece[m_selected].getPos().x - 50;
		int y = m_piece[m_selected].getPos().y - 50;

		std::cout << x << " " << y << std::endl;

		int left2 = x / 80;
		int right2 = 7 - left2;

		int up2 = y / 80;
		int down2 = 7 - up2;

		std::cout << " " << up2 << std::endl;
		std::cout << left2 << " " << right2 << std::endl;
		std::cout << " " << down2 << std::endl;

		for (int i = 1; i <= up2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}
			
			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= down2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= right2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= left2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(left, i));
			m_possibleMoves.push_back(m_shape);
		}
	}

	else if (m_piece[m_selected].getType() == 'B')
	{
		int x = m_piece[m_selected].getPos().x - 50;
		int y = m_piece[m_selected].getPos().y - 50;

		std::cout << x << " " << y << std::endl;

		int left2 = x / 80;
		int right2 = 7 - left2;
		int up2 = y / 80;
		int down2 = 7 - up2;

		int upleft = (up2 > left2) ? left2 : up2;
		int upright = (up2 > right2) ? right2 : up2;
		int downleft = (down2 > left2) ? left2 : down2;
		int downright = (down2 > right2) ? right2 : down2;

		for (int i = 1; i <= upleft; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up + left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up + left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + left, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= upright; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up + right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up + right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= downright; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down + right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down + right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= downleft; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down + left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down + left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}
			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + left, i));
			m_possibleMoves.push_back(m_shape);
		}
	}
	else if (m_piece[m_selected].getType() == 'Q')
	{
		int x = m_piece[m_selected].getPos().x - 50;
		int y = m_piece[m_selected].getPos().y - 50;

		std::cout << x << " " << y << std::endl;

		int left2 = x / 80;
		int right2 = 7 - left2;
		int up2 = y / 80;
		int down2 = 7 - up2;

		int upleft = (up2 > left2) ? left2 : up2;
		int upright = (up2 > right2) ? right2 : up2;
		int downleft = (down2 > left2) ? left2 : down2;
		int downright = (down2 > right2) ? right2 : down2;

		for (int i = 1; i <= up2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= down2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= right2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}
			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= left2; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}
			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(left, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= upleft; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up + left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up + left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + left, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= upright; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(up + right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(up + right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(up + right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= downright; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down + right, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down + right, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + right, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}
			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + right, i));
			m_possibleMoves.push_back(m_shape);
		}

		for (int i = 1; i <= downleft; i++)
		{
			bool can_break = false;

			for (int j = 0; j < 16; j++)
			{
				if (m_piece[j].dead() == false)
				{

					if (m_piece[j].getPos() == m_piece[m_selected].getPos() + multiply(down + left, i))
					{
						can_break = true;
						break;
					}
					if (m_pieceE[j].getPos() == m_piece[m_selected].getPos() + multiply(down + left, i))
					{
						can_break = true;
						m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + left, i));
						m_possibleMoves.push_back(m_shape);
						break;
					}
				}
			}

			if (can_break)
				break;

			m_shape.setPosition(m_piece[m_selected].getPos() + multiply(down + left, i));
			m_possibleMoves.push_back(m_shape);
		}
	}
	else if (m_piece[m_selected].getType() == 'K')
	{
		bool b_up = true;
		bool b_upleft = true;
		bool b_upright = true;
		bool b_down = true;
		bool b_downleft = true;
		bool b_downright = true;
		bool b_left = true;
		bool b_right = true;

		for (int i = 0; i < 16; i++)
		{
			if(m_piece[i].dead() == false)
			{

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + up			or (m_piece[m_selected].getPos() + up).y < 0)
					b_up = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + up + left		or (m_piece[m_selected].getPos() + up + left).y < 0			or (m_piece[m_selected].getPos() + up + left).x < 0)
					b_upleft = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + up + right	or (m_piece[m_selected].getPos() + up + right).y < 0		or (m_piece[m_selected].getPos() + up + right).x > 610)
					b_upright = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + down			or (m_piece[m_selected].getPos() + down).y > 610)
					b_down = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + down + left	or (m_piece[m_selected].getPos() + down + left).y > 610		or (m_piece[m_selected].getPos() + down + left).x < 0)
					b_downleft = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + down + right	or (m_piece[m_selected].getPos() + down + right).y > 610	or (m_piece[m_selected].getPos() + down + right).x > 610)
					b_downright = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + left			or (m_piece[m_selected].getPos() + left).x < 0)
					b_left = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + right			or (m_piece[m_selected].getPos() + right).x > 610)
					b_right = false;
			}
			
		}

		if (b_upleft)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + up + left);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_up)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + up);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_upright)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + up + right);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_right)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + right);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_downright)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + right + down);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_down)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + down);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_downleft)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + down + left);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_left)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + left);
			m_possibleMoves.push_back(m_shape);
		}
	}
	else if (m_piece[m_selected].getType() == 'H')
	{
		bool b_upupleft = true;
		bool b_upupright = true;
		bool b_rightrightup = true;
		bool b_rightrightdown = true;
		bool b_downdownleft = true;
		bool b_downdownright = true;
		bool b_leftleftup = true;
		bool b_leftleftdown = true;

		for (int i = 0; i < 16; i++)
		{
			if(m_piece[i].dead() == false)
			{

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + up + up + left		or (m_piece[m_selected].getPos() + up + up + left).y < 0			or (m_piece[m_selected].getPos() + up + up + left).x < 0)
					b_upupleft = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + up + up + right		or (m_piece[m_selected].getPos() + up + up + right).y < 0			or (m_piece[m_selected].getPos() + up + up + right).x > 610)
					b_upupright = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + right + right + up	or (m_piece[m_selected].getPos() + right + right + up).y < 0		or (m_piece[m_selected].getPos() + right + right + up).x > 610)
					b_rightrightup = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + right + right + down	or (m_piece[m_selected].getPos() + right + right + down).y > 610	or (m_piece[m_selected].getPos() + right + right + down).x > 610)
					b_rightrightdown = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + down + down + left	or (m_piece[m_selected].getPos() + down + down + left).y > 610		or (m_piece[m_selected].getPos() + down + down + left).x < 0)
					b_downdownleft = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + down + down + right	or (m_piece[m_selected].getPos() + down + down + right).y > 610		or (m_piece[m_selected].getPos() + down + down + right).x > 610)
					b_downdownright = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + left + left + up		or (m_piece[m_selected].getPos() + left + left + up).y < 0			or (m_piece[m_selected].getPos() + left + left + up).x < 0)
					b_leftleftup = false;

				if (m_piece[i].getPos() == m_piece[m_selected].getPos() + left + left + down	or (m_piece[m_selected].getPos() + left + left + down).y > 610		or (m_piece[m_selected].getPos() + left + left + down).x < 0)
					b_leftleftdown = false;
			}

		}

		if (b_upupleft)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + up + up + left);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_upupright)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + up + up + right);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_rightrightup)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + right + right + up);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_rightrightdown)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + right + right + down);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_downdownleft)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + down + down + left);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_downdownright)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + down + down + right);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_leftleftup)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + left + left + up);
			m_possibleMoves.push_back(m_shape);
		}
		if (b_leftleftdown)
		{
			m_shape.setPosition(m_piece[m_selected].getPos() + left + left + down);
			m_possibleMoves.push_back(m_shape);
		}
	}
}

void Army::drawPossibleMoves(sf::RenderWindow* window)
{
	for (int i = 0; i < m_possibleMoves.size(); i++)
		window->draw(m_possibleMoves[i]);
}

sf::Vector2f Army::multiply(sf::Vector2f a, int b)
{
	int x = a.x * b;
	int y = a.y * b;

	return sf::Vector2f(x, y);
}
