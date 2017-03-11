#include "King.hpp"

King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "King";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(kingWhite);
	}
	else
	{
		sprite.setTexture(kingBlack);
	}
	offsets = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
		{1, 1},
		{-1, 1},
		{-1, -1},
		{1, -1}
	};
	offsetContinue = false;
}

King::~King()
{
}