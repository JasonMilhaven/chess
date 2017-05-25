#include <thread>
#include <mutex>
#include <sstream>
#include <vector>

#include "SFML\Graphics.hpp"

#include "Path.hpp"

#include "Network.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Pawn.hpp"

using namespace sf;
using namespace std;

const string FILENAME_FONT = PATH + "calibri.ttf";
const string FILENAME_BOARD = PATH + "board.png";
const string FILENAME_HIGHLIGHT = PATH + "highlight.png";
const int WIN_WIDTH = 400;
const int WIN_HEIGHT = 400;
const string WIN_TITLE = "Chess_v2";
const string DEFAULT_IP = "localhost";
const int DEFAULT_PORT = 38897;

bool isRunning = true;
bool inGame = false;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE, Style::Close | Style::Titlebar);
thread thr_main;
thread thr_console;
std::mutex mutexHighlights;
Network *network = nullptr;
Piece *selectedPiece = nullptr;
list<Piece*> pieces;
list<Sprite> highlights;
bool isLocalPlayerWhite = false;
bool isWhiteTurn = true;
Piece promotionPiece = Queen(0, 0, false);

string ip = "";
int port = 0;
string textInput = ""; // use for text input
Font font;
Texture boardTexture;
Texture highlightTexture;
Sprite board;

// main menu
RectangleShape rHost;
Text tHost;
RectangleShape rConnect;
Text tConnect;
RectangleShape rAddress;
Text tAddress;

void init_resources()
{
	boardTexture.loadFromFile(FILENAME_BOARD);
	board = Sprite(boardTexture);
	highlightTexture.loadFromFile(FILENAME_HIGHLIGHT);
	//highlight = Sprite(highlightTexture);
}

std::list<Piece*> &get_pieces()
{
	return pieces;
}

void clear_highlights()
{
	highlights.clear();
}

int to_px(int v)
{
	int ret = v * Piece::TEXTURE_SIZE - Piece::TEXTURE_SIZE;
	return ret;
}

/*const bool get_is_running()
{
	return window.isOpen();
}*/

//string *split_str(string s)
vector<string> split_str(string s)
{
	vector<string> v;
	istringstream iss(s);
	for (string s; iss >> s; )
	{
		v.push_back(s);
	}
	return v;
}

void create_pawns(int col, bool isWhite)
{
	for (int i = 1; i < 9; i++)
	{
		pieces.push_back(new Pawn(i, col, isWhite));
	}
}

void create_others(int col, bool isWhite)
{
	pieces.push_back(new Rook(1, col, isWhite));
	pieces.push_back(new Knight(2, col, isWhite));
	pieces.push_back(new Bishop(3, col, isWhite));
	pieces.push_back(new King(4, col, isWhite));
	pieces.push_back(new Queen(5, col, isWhite));
	pieces.push_back(new Bishop(6, col, isWhite));
	pieces.push_back(new Knight(7, col, isWhite));
	pieces.push_back(new Rook(8, col, isWhite));

	/*Bishop *testBishop = new Bishop(4 + isWhite, 5, isWhite);
	pieces.push_back(testBishop);*/
}

const bool &get_turn_color()
{
	return isWhiteTurn;
}

void set_white_turn(bool v)
{
	isWhiteTurn = v;
}

const bool &get_local_player_color()
{
	return isLocalPlayerWhite;
}

void set_local_player_color(bool isWhite)
{
	cout << "You are ";
	if (isWhite)
	{
		cout << "white";
	}
	else
	{
		cout << "black";
	}
	cout << ".\n";
	isLocalPlayerWhite = isWhite;
}

void on_game_start()
{
	inGame = true;
}

void on_game_end()
{
	if (network != nullptr)
	{
		network->safe_delete();
		network = nullptr;
	}

	list<Piece*>::iterator i;
	for (i = pieces.begin(); i != pieces.end(); i++)
	{
		delete (*i);
	}
	pieces.clear();

	inGame = false;
}

void recalc_address()
{
	string a = "";
	string b = "";
	bool foundColon = false;
	for (int i = 0; i < textInput.length(); i++)
	{
		char c = textInput.at(i);
		if (c == ':')
		{
			foundColon = true;
		}
		else
		{
			if (foundColon)
			{
				b += c;
			}
			else
			{
				a += c;
			}
		}
	}

	ip = a;
	port = atoi(b.c_str());

	if (a == "")
	{
		ip = DEFAULT_IP;
	}
	if (port == 0)
	{
		port = DEFAULT_PORT;
	}
}

bool is_mouse_over_piece(Event &e, Piece &p)
{
	bool ret = false;

	int mX = e.mouseButton.x;
	int mY = e.mouseButton.y;

	int pX = to_px(p.get_x());
	int pY = to_px(p.get_y());

	bool xCondition = mX <= (pX + Piece::TEXTURE_SIZE) && mX > pX;
	bool yCondition = mY <= (pY + Piece::TEXTURE_SIZE) && mY > pY;

	ret = xCondition && yCondition;
	return ret;
}

bool is_mouse_over_button(Event &e, RectangleShape &r)
{
	bool ret = false;
	int x = e.mouseButton.x;
	int y = e.mouseButton.y;
	
	bool xCondition = x <= (r.getPosition().x + r.getSize().x) && x >= r.getPosition().x;
	bool yCondition = y <= (r.getPosition().y + r.getSize().y) && y >= r.getPosition().y;

	if (xCondition && yCondition)
	{
		ret = true;
	}

	return ret;
}

void update()
{
	string cmd = network->get_cmd();
	
	if (!(cmd == ""))
	{
		//cout << "cmd in: " << cmd << endl;
		if (cmd.find("color ") != string::npos)
		{
			bool color = (char)cmd[6] - '0';
			set_local_player_color(color);
		}
		if (cmd.find("client_ready") != string::npos || cmd.find("color ") != string::npos)
		{
			create_others(1, true);
			create_pawns(2, true);

			create_others(8, false);
			create_pawns(7, false);
		}
		if (cmd.find("move ") != string::npos)
		{
			int atX, atY, toX, toY;

			atX = (char)cmd[5] - '0';
			atY = (char)cmd[7] - '0';
			toX = (char)cmd[9] - '0';
			toY = (char)cmd[11] - '0';

			std::list<Piece*>::iterator pIterator;
			for (pIterator = get_pieces().begin(); pIterator != get_pieces().end(); pIterator++) // if a piece exists at x and y
			{
				Piece *p = *pIterator;

				if (p->get_x() == atX && p->get_y() == atY)
				{
					p->move(toX, toY);
				}
			}
		}
		if (cmd.find("msg ") != string::npos)
		{
			cout << "Opponent:" << cmd.substr(3, cmd.size() - 1) << endl;
		}
	}
}

void draw()
{
	window.clear(Color(0, 0, 0));

	if (inGame)
	{
		window.draw(board);

		list<Piece*>::iterator i;
		for (i = pieces.begin(); i != pieces.end(); i++)
		{
			int drawX = to_px((*i)->get_x());
			int drawY = to_px((*i)->get_y());

			Sprite s = (*i)->get_sprite();
			s.setPosition(Vector2f(drawX, drawY));
			window.draw(s);
		}

		mutexHighlights.lock();
		list<Sprite>::iterator h;
		for (h = highlights.begin(); h != highlights.end(); h++)
		{
			if (get_turn_color() == get_local_player_color())
			{
				window.draw(*h);
			}
		}
		mutexHighlights.unlock();
	}
	else
	{
		window.draw(rHost);
		window.draw(tHost);
		window.draw(rConnect);
		window.draw(tConnect);
		window.draw(rAddress);
		window.draw(tAddress);
	}

	window.display();
}

void main_loop()
{
	while (window.isOpen())
	{
		draw();

		if (network != nullptr) {
			if (network->get_is_running()) {
				update();
			}
		}
	}
}

void input_loop()
{
	window.setActive(false);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				if (inGame)
				{
					on_game_end();
				}
				else
				{
					window.close();
				}
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (inGame)
					{
						std::list<Piece*>::iterator i;
						for (i = pieces.begin(); i != pieces.end(); i++)
						{
							if (is_mouse_over_piece(e, **i) && ((*i)->get_is_white() == isLocalPlayerWhite))
							{
								mutexHighlights.lock();
								highlights.clear();
								for (int a = 1; a <= 8; a++)
								{
									for (int b = 1; b <= 8; b++)
									{
										if ((*i)->can_move(a, b))
										{
											Sprite highlight = Sprite(highlightTexture);
											highlight.setPosition(to_px(a), to_px(b));
											highlights.push_back(highlight);
										}
									}
								}
								mutexHighlights.unlock();
								selectedPiece = &**i;
								break;
							}
							else
							{
								selectedPiece = nullptr;
							}
						}
					}
					else
					{
						recalc_address();
						if (is_mouse_over_button(e, rHost))
						{
							network = new Server(port);
							on_game_start();
						}
						else if (is_mouse_over_button(e, rConnect))
						{
							network = new Client(port, ip);
							on_game_start();
						}
					}
				}
				else if (e.mouseButton.button == Mouse::Button::Right)
				{
					if (selectedPiece != nullptr && isLocalPlayerWhite == isWhiteTurn)
					{
						int x = (e.mouseButton.x / Piece::TEXTURE_SIZE) + 1;
						int y = (e.mouseButton.y / Piece::TEXTURE_SIZE) + 1;

						if (selectedPiece->can_move(x, y))
						{							
							network->send_cmd(
								"move " +
								to_string(selectedPiece->get_x()) + " " +
								to_string(selectedPiece->get_y()) + " " +
								to_string(x) + " " +
								to_string(y)
							);
							selectedPiece->move(x, y);
						}
					}
				}
			}
			else if (e.type == Event::TextEntered)
			{
				Text *currentTextInput = &tAddress;
				if (inGame)
				{
					// placeholder for changing the text input
					// if in game, change to the chat textbox
				}
				if (e.text.unicode < 128)
				{
					char c = static_cast<char>(e.text.unicode);
					if (c == '\b')
					{
						if (textInput.size() >= 1)
						{
							textInput.erase(textInput.size() - 1);
						}
					}
					else
					{
						textInput += c;
					}
					currentTextInput->setString(textInput);
				}
			}
		}
	}
}

void console_loop()
{
	cout << "Commands:\n/s [msg]\n/p []\n";

	while (window.isOpen())
	{
		string input;
		getline(cin, input);

		if (input.size() > 3)
		{
			if (input.find("/s ") != string::npos)
			{
				if (network != nullptr)
				{
					network->send_cmd("msg " + input.substr(3, input.size() - 1));
				}
			}
			else if (input.find("/p ") != string::npos)
			{
				string pro = input.substr(3, input.size() - 1);
				bool valid = false;

				if (pro == "knight")
				{
					promotionPiece = Knight();
					valid = true;
				}
				else if (pro == "bishop")
				{
					promotionPiece = Bishop();
					valid = true;
				}
				else if (pro == "rook" || pro == "castle")
				{
					promotionPiece = Rook();
					valid = true;
				}
				else if (pro == "queen")
				{
					promotionPiece = Queen();
					valid = true;
				}

				if (valid)
				{
					cout << "Pawns will now promote to " << pro << ".\n";
				}
				else
				{
					cout << "Failed to set promotion.\n";
				}
			}
		}
	}
}

void on_exit()
{
	thr_console.join();
	thr_main.join();
}

void init()
{
	font.loadFromFile(FILENAME_FONT);

	// ui initialization

	rHost = RectangleShape(Vector2f(200, 25));
	rHost.setFillColor(Color(0, 0, 255));
	rHost.setPosition(Vector2f(100, 50));

	tHost = Text("host", font, 20);
	tHost.setPosition(Vector2f(105, 50));

	rConnect = RectangleShape(Vector2f(200, 25));
	rConnect.setFillColor(Color(0, 150, 150));
	rConnect.setPosition(Vector2f(100, 100));

	tConnect = Text("connect", font, 20);
	tConnect.setPosition(Vector2f(105, 100));

	rAddress = RectangleShape(Vector2f(200, 25));
	rAddress.setFillColor(Color(0, 255, 0));
	rAddress.setPosition(Vector2f(100, 150));

	tAddress = Text("ip:port", font, 20);
	tAddress.setPosition(Vector2f(105, 150));

	//currentTextInput = &tAddress;

	// end ui initialization

	thr_console = thread(console_loop);
	thr_main = thread(main_loop); // begin the game and draw loop
	input_loop(); // begin the input loop

	on_exit(); // when loops are over, cleanup program
}