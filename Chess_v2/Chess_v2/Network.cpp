#include "Network.hpp"

void Network::do_init()
{
	init();

	//while (get_is_running()) //thr != nullptr
	while (isRunning)
	{
		loop();
	}
}

void Network::init()
{
}

void Network::loop()
{
	char buffer[CMD_SIZE];
	std::size_t received;
	if (clientSocket.receive(buffer, CMD_SIZE, received) != sf::Socket::Done)
	{
		on_game_end();
	}
	cmd = string(buffer);
}

void Network::start()
{
	thr = new std::thread(&Network::do_init, this);
}

const bool Network::get_is_running()
{
	return isRunning;
}

string Network::get_cmd()
{
	string tempCmd = cmd;
	cmd = "";
	return tempCmd;
}

void Network::send_cmd(string cmd)
{
	clientSocket.send(cmd.c_str(), cmd.size() + 1);
}

Network::Network(int port)
{
	//std::cout << "created Network instance with port " << port << std::endl;
	isRunning = true;
	thr = nullptr;
	delete_thr = nullptr;
	this->port = port;
	cmd = "";
}

Network::~Network()
{
	isRunning = false;
	clientSocket.disconnect();
	if (thr != nullptr)
	{
		thr->join();
		delete thr;
	}
	if (delete_thr != nullptr)
	{
		// note detatch seems to work, where join doesn't?
		delete_thr->detach();
		delete delete_thr;
	}
}

void Network::do_delete()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	delete this;
}

void Network::safe_delete()
{
	delete_thr = new thread(&Network::do_delete, this);
}