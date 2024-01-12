#include "Piece.h"

void Piece::draw(sf::RenderWindow* window)
{
	window->draw(m_piece);
}

// pawn		1669 58
// tower	1338 58
// horse	997  44
// bishop	667	 33
// queen	343	 33
// king		36	 37

void Piece::loadTexture(std::string name, sf::Vector2f pos)
{
	m_type = name;
	m_dead = false;

	std::string path;
	path.append("Assets/");
	path.append(name);
	path.append(".png");
	if (!m_text.loadFromFile(path, sf::IntRect(0, 0, 64, 64)))
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	else
	{
		m_piece.setSize(sf::Vector2f(64.f, 64.f));
		m_piece.setOrigin(sf::Vector2f(32.f, 32.f));
		m_piece.setTexture(&m_text);
		m_piece.setPosition(pos);
	}
}

sf::RectangleShape* Piece::getShape()
{
	return &m_piece;
}
