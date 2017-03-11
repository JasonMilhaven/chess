#include "Client.hpp"

void Client::init()
{
	clientSocket.connect(ip, port);
	send_cmd("client_ready");
}

/*void Client::loop()
{
}*/

Client::Client(int port, string ip) : Network(port)
{
	this->ip = ip;

	start();
}

Client::~Client()
{
}