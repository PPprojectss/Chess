#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
	public:
		Piece() = default;
		~Piece() = default;

		void draw(sf::RenderWindow* window);
		void loadTexture(std::string name, sf::Vector2f pos);
		sf::RectangleShape* getShape();

	private:
		sf::RectangleShape m_piece;
		sf::Texture m_text;
		bool m_dead;
		std::string m_type;
};

