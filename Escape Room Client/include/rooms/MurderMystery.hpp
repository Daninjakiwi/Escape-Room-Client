#pragma once
#include "Room.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"
#include "core/GameObject.hpp"
#include "objects/floor.hpp"

class MurderMystery : public Room {
private:
	volt::PbrMaterial mat;
	Button btn_start;
	std::string username;
	wall floor;
public:
	MurderMystery(const std::string& data);

	void LocalUpdate(Environment& env);
	void Draw(volt::Window& window);
};
