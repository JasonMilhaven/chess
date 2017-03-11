#include "Queen.hpp"

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "Queen";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(queenWhite);
	}
	else
	{
		sprite.setTexture(queenBlack);
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
	offsetContinue = true;
}

Queen::~Queen()
{
}