#pragma once

#include <random>

#include "Network.hpp"

class Server : public Network
{

private:
	sf::TcpListener serverSocket;

	void init() override;
	//void loop() override;

public:
	Server(int port);
	~Server();

};