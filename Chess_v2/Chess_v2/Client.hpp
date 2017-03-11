#pragma once

#include "Network.hpp"

class Client : public Network
{

private:
	string ip;

	void init() override;
	//void loop() override;

public:
	Client(int port, string ip);
	~Client();

};