#pragma once

#define CMD_SIZE 512

#include <list>

class Piece;

//const bool get_is_running();
std::list<Piece*> &get_pieces();
void on_game_end();

const bool &get_turn_color();
void set_white_turn(bool v);

const bool &get_local_player_color();
void set_local_player_color(bool isWhite);

void clear_highlights();

void init();
void init_resources();