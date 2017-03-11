#pragma once

#include "Piece.hpp"

class Queen : public Piece
{

public:
	Queen(int x = 0, int y = 0, bool isWhite = false);
	~Queen();

};