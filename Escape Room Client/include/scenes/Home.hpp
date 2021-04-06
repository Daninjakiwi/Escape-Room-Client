#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"


class Home : public Scene {
public:
	bool guest;
	Button join, host, settings, go;
	InputField code;
	bool show_code;
	static bool waiting;
	static std::string* room_code;
public:
	Home();

	void Update(Environment& env);
	void Draw(volt::Window& window);

	static void RecieveMessage(const std::string& msg);
};
