#include "Server.hpp"

void Server::init()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 1);

	int randN = uni(rng);
	bool toBool = randN;

	serverSocket.listen(port);
	serverSocket.accept(clientSocket);
	
	send_cmd("color " + std::to_string(randN));
	set_local_player_color(!toBool);
}

/*void Server::loop()
{
}*/

Server::Server(int port) : Network(port)
{
	start();
}

Server::~Server()
{
	serverSocket.close();
}