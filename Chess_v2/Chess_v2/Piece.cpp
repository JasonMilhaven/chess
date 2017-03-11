#include "Piece.hpp"

const std::string Piece::FILENAME_PIECES = PATH + "pieces.png";

Texture Piece::pawnWhite = Texture();
Texture Piece::rookWhite = Texture();
Texture Piece::knightWhite = Texture();
Texture Piece::bishopWhite = Texture();
Texture Piece::queenWhite = Texture();
Texture Piece::kingWhite = Texture();

Texture Piece::pawnBlack = Texture();
Texture Piece::rookBlack = Texture();
Texture Piece::knightBlack = Texture();
Texture Piece::bishopBlack = Texture();
Texture Piece::queenBlack = Texture();
Texture Piece::kingBlack = Texture();

void Piece::init_textures()
{
	pawnWhite.loadFromFile(FILENAME_PIECES, IntRect(5 * TEXTURE_SIZE, 0, TEXTURE_SIZE, TEXTURE_SIZE));
	rookWhite.loadFromFile(FILENAME_PIECES, IntRect(4 * TEXTURE_SIZE, 0 * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	knightWhite.loadFromFile(FILENAME_PIECES, IntRect(3 * TEXTURE_SIZE, 0, TEXTURE_SIZE, TEXTURE_SIZE));
	bishopWhite.loadFromFile(FILENAME_PIECES, IntRect(2 * TEXTURE_SIZE, 0, TEXTURE_SIZE, TEXTURE_SIZE));
	queenWhite.loadFromFile(FILENAME_PIECES, IntRect(TEXTURE_SIZE, 0, TEXTURE_SIZE, TEXTURE_SIZE));
	kingWhite.loadFromFile(FILENAME_PIECES, IntRect(0, 0, TEXTURE_SIZE, TEXTURE_SIZE));

	pawnBlack.loadFromFile(FILENAME_PIECES, IntRect(5 * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	rookBlack.loadFromFile(FILENAME_PIECES, IntRect(4 * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	knightBlack.loadFromFile(FILENAME_PIECES, IntRect(3 * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	bishopBlack.loadFromFile(FILENAME_PIECES, IntRect(2 * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	queenBlack.loadFromFile(FILENAME_PIECES, IntRect(TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
	kingBlack.loadFromFile(FILENAME_PIECES, IntRect(0, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE));
}

const std::string &Piece::get_name()
{
	return name;
}

const Sprite &Piece::get_sprite()
{
	return sprite;
}

const bool Piece::get_is_white()
{
	return isWhite;
}

void Piece::set_is_white(bool v)
{
	isWhite = v;
}

const int &Piece::get_x()
{
	return x;
}

const int &Piece::get_y()
{
	return y;
}

const double &Piece::get_value()
{
	return value;
}

bool Piece::can_move(int x, int y)
{
	bool ret = false;

	/*if (get_x() == x && get_y() == y)
	{
		ret = true;
	}*/

	int range = 1;

	if (offsetContinue)
	{
		range = 8;
	}

	std::vector<std::vector<int>>::iterator m;
	//std::list<std::list<int>>::iterator m;
	for (m = offsets.begin(); m < offsets.end(); m++)
	//for (m = offsets.begin(); m != offsets.end(), m++)
	{
		for (int i = 1; i <= range; i++)
		{
			int xTarget = (*m)[0] * i + get_x();
			int yTarget = (*m)[1] * i + get_y();			

			std::list<Piece*>::iterator pIterator;
			for (pIterator = get_pieces().begin(); pIterator != get_pieces().end(); pIterator++) // if a piece exists at x and y
			{
				Piece *p = *pIterator;

				if (p->get_x() == xTarget && p->get_y() == yTarget)
				{
					ret = false;
				}
			}

			if (x == xTarget && y == yTarget)
			{
				return true;
			}
		}
	}

	return ret;
}

void Piece::move(int x, int y)
{
	set_white_turn(!get_is_white());
	clear_highlights();

	std::list<Piece*>::iterator pIterator;
	for (pIterator = get_pieces().begin(); pIterator != get_pieces().end(); pIterator++) // if a piece exists at x and y
	{
		Piece *p = *pIterator;

		if (p->get_x() == x && p->get_y() == y)
		{
			if (p->get_is_white() != get_is_white())
			{
				get_pieces().remove(p);
				delete p;
			}
		}
	}

	this->x = x;
	this->y = y;
}

Piece::Piece(int x, int y, bool isWhite)
{
	this->isWhite = isWhite;
	this->x = x;
	this->y = y;
}

Piece::~Piece()
{
}