#pragma once

#include "core/Scene.hpp"



#include "ui/Button.hpp"
#include "core/Network.hpp"

class MainMenu : public Scene {
public:
	static bool server_connected;
	static bool is_connecting;
	static bool connection_failed;

	Button guest, login, create, again;
	Label connecting, failed;
public:
	MainMenu();

	void Update(Environment& env);
	void Draw(volt::Window& window);

	static void MessageFeed(const std::string& message);
	static void AttemptConnection(UdpConnection* server);
};