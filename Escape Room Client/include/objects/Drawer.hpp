#pragma once

#include "core/GameObject.hpp"
#include "Desk.hpp"

class Drawer : public GameObject {
private:
	bool has_key;
	int index;
	bool locked;
	bool is_open;
	bool looking;
public:
	Drawer(int index);

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};