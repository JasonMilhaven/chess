#pragma once

#include "Piece.hpp"

class Bishop : public Piece
{

public:
	Bishop(int x = 0, int y = 0, bool isWhite = false);
	~Bishop();

};