#pragma once

#include "Piece.hpp"

class Rook : public Piece
{

public:
	Rook(int x = 0, int y = 0, bool isWhite = false);
	~Rook();

};