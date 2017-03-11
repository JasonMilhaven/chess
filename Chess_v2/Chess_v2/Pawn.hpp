#pragma once

#include "Piece.hpp"

class Pawn : public Piece
{

private:
	bool firstMove;

public:
	bool can_move(int x, int y) override;
	void move(int x, int y) override;
	Pawn(int x = 0, int y = 0, bool isWhite = false);
	~Pawn();

};