#pragma once

#include <iostream>
#include <thread>

#include "SFML\Network.hpp"

#include "Program.hpp"

using std::string;
using std::thread;

class Network
{

private:
	bool isRunning;
	thread *thr;
	thread *delete_thr;

	void do_init();
	virtual void init();
	virtual void loop();
	void do_delete();

protected:
	int port;
	string cmd;
	sf::TcpSocket clientSocket;

	void start();
	virtual ~Network();

public:
	const bool get_is_running();
	string get_cmd();
	void send_cmd(string cmd);
	Network(int port);
	void safe_delete();

};