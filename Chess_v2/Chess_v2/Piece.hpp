#pragma once

#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "SFML\Graphics.hpp"

#include "Path.hpp"
#include "Program.hpp"

using namespace sf;

class Piece
{

private:
	const static std::string FILENAME_PIECES;

protected:
	static Texture pawnWhite;
	static Texture rookWhite;
	static Texture knightWhite;
	static Texture bishopWhite;
	static Texture queenWhite;
	static Texture kingWhite;

	static Texture pawnBlack;
	static Texture rookBlack;
	static Texture knightBlack;
	static Texture bishopBlack;
	static Texture queenBlack;
	static Texture kingBlack;

	std::string name;
	Sprite sprite;
	bool isWhite;
	int x, y;
	double value;
	std::vector<std::vector<int>> offsets;
	//std::list<std::list<int>> offsets;
	bool offsetContinue;

	Piece(int x = 0, int y = 0, bool isWhite = false);

public:
	const static int TEXTURE_SIZE = 50;

	static void init_textures();

	const std::string &get_name();
	const Sprite &get_sprite();
	//inline Sprite *get_sprite_ptr() { return &sprite; };
	const int &get_x();
	const int &get_y();
	const double &get_value();
	virtual bool can_move(int x, int y);
	virtual void move(int x, int y);
	const bool get_is_white();
	void set_is_white(bool v);
	virtual ~Piece();

};