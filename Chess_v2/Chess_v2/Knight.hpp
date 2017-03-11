#pragma once

#include "Piece.hpp"

class Knight : public Piece
{

public:
	Knight(int x = 0, int y = 0, bool isWhite = false);
	~Knight();

};