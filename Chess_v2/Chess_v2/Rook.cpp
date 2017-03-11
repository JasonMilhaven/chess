#include "Rook.hpp"

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "Rook";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(rookWhite);
	}
	else
	{
		sprite.setTexture(rookBlack);
	}
	offsets = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1}
	};
	offsetContinue = true;
}

Rook::~Rook()
{
}