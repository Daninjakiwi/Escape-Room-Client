#pragma once

#include "core/GameObject.hpp"

class SmartShoes : public GameObject {
private:
	bool has_activated;
	bool is_looking;
public:
	SmartShoes();

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};