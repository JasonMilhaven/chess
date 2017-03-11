#include "Program.hpp"
#include "Piece.hpp"

int main()
{
	init_resources(); // load sprites w/ their textures
	Piece::init_textures();
	Program();
}