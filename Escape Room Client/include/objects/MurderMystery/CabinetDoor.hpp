#pragma once

#include "core/GameObject.hpp"

class CabinetDoor : public GameObject {
private:
	int index;
	bool has_key;
	bool is_locked;
	bool is_open;
	bool looking;
public:
	CabinetDoor(int index);

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};