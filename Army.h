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
		void game(sf::RenderWindow* window, bool turn);

	private:

		Board m_board;

		int m_selected;
		bool m_mousePressed;

		Piece m_piece[16];
		Piece m_pieceE[16];
};

