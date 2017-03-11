#include "Bishop.hpp"

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "Bishop";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(bishopWhite);
	}
	else
	{
		sprite.setTexture(bishopBlack);
	}
	offsets = {
		{1, 1},
		{-1, 1},
		{-1, -1},
		{1, -1}
	};
	offsetContinue = true;
}

Bishop::~Bishop()
{
}