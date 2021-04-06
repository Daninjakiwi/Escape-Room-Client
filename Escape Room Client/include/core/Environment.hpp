#pragma once
#include <Volt.hpp>
#include "Network.hpp"

struct Environment {
	volt::Window* window;
	void* scene;
	std::string token;
	std::string ip;
	int port;
	std::string code;
	UdpConnection* server;
	std::string username;
};
