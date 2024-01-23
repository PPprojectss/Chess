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

		char getType();
		bool firstMove();
		bool dead();
		void die();
		void setPos(sf::Vector2f pos);
		sf::Vector2f getPos();
		void reset();

	private:
		sf::RectangleShape m_piece;
		sf::Texture m_text;
		bool m_dead = false;
		bool m_firstMove = true;
		std::string m_name;
		char m_type;

		sf::Vector2f m_pos;
};

