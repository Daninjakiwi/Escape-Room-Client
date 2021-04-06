#pragma once
#include "Room.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"
#include "core/GameObject.hpp"

class MurderMystery : public Room {
private:
	Button btn_start;
	std::string username;
public:
	MurderMystery(const std::string& data);

	void LocalUpdate(Environment& env);
	void Draw(volt::Window& window);
};
