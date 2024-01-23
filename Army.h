#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Piece.h"
#include "Board.h"

class Army
{
	public:
		Army(bool white);
		~Army() = default;

		void draw(sf::RenderWindow* window);
		std::string game(sf::RenderWindow* window);
		void updatePiece(int id, sf::Vector2f pos);
		void updatePossibleMoves(sf::RenderWindow* window);
		void drawPossibleMoves(sf::RenderWindow* window);
		sf::Vector2f multiply(sf::Vector2f a, int b);


	private:

		Board m_board;

		int m_selected;
		bool m_mousePressed;
		bool m_white;
		bool m_valid = false;

		std::vector<sf::RectangleShape> m_possibleMoves;


		Piece m_piece[16];
		Piece m_pieceE[16];
};

