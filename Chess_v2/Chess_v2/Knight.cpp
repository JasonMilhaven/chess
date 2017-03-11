#include "Knight.hpp"

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "Knight";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(knightWhite);
	}
	else
	{
		sprite.setTexture(knightBlack);
	}
	offsets = {
		{-1, 2},
		{1, 2},
		{-2, 1},
		{-2, -1},
		{-1, -2},
		{1, -2},
		{2, -1},
		{2, 1}
	};
	offsetContinue = false;
}

Knight::~Knight()
{
}