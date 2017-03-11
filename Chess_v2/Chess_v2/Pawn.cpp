#include "Pawn.hpp"

bool Pawn::can_move(int x, int y)
{
	bool ret = Piece::can_move(x, y);

	/*while (offsets.size() > 1)
	{
		offsets.erase(offsets.begin() + 1);
	}*/
	// ensure the pawn has it's first offset

	if (firstMove)
	{
		if (get_x() == x && (get_y() + offsets[0][1] * 2) == y)
		{
			ret = true;
		}
	}

	std::list<Piece*>::iterator pIterator;
	for (pIterator = get_pieces().begin(); pIterator != get_pieces().end(); pIterator++) // if a piece exists at x and y
	{
		Piece *p = *pIterator;

		if (p->get_x() == x && p->get_y() == y)
		{
			if (p->get_is_white() == !get_is_white())
			{
				if (abs(p->get_x() - get_x()) == 1 && p->get_y() == (get_y() + offsets[0][1]))
				{
					ret = true;
				}
			}
		}
	}

	return ret;
}

void Pawn::move(int x, int y)
{
	firstMove = false;
	Piece::move(x, y);
}

Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite)
{
	name = "Pawn";
	value = 5;
	if (isWhite)
	{
		sprite.setTexture(pawnWhite);
	}
	else
	{
		sprite.setTexture(pawnBlack);
	}
	int yOff = -1;
	if (isWhite)
	{
		yOff = 1;
	}
	offsets = {
		{0, yOff}
	};
	offsetContinue = false;
	firstMove = true;
}

Pawn::~Pawn()
{
}