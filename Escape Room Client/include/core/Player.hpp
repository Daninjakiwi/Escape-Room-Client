#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
	static Player* player;
private:
	std::string name;
	volt::Vec3 velocity;
	volt::Camera camera;
public:
	Player(const std::string& username);

	void Update(Environment& env);

	void Draw(volt::Window& window);

	std::string& GetName();
};