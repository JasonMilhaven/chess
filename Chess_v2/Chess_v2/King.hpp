#pragma once

#include "Piece.hpp"

class King : public Piece
{

public:
	King(int x = 0, int y = 0, bool isWhite = false);
	~King();

};