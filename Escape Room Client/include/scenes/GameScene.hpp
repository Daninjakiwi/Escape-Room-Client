#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"
#include "rooms/Room.hpp"
#include "core/Network.hpp"


class GameScene : public Scene {
public:
	static Room* room;
	static bool ready;
	static std::string msg;
public:
	GameScene();
	~GameScene();

	void Update(Environment& env);
	void Draw(volt::Window& window);

	void LoadRoom(Environment& env);

	static void StartUpListen(const std::string& message);
	static void Listen(const std::string& message);
};
