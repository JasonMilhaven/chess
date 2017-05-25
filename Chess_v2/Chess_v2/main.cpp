#include "Program.hpp"
#include "Piece.hpp"

int main()
{
	init_resources(); // load sprites
	Piece::init_textures(); // load piece textures
	init(); // init Program
	return 0;
}