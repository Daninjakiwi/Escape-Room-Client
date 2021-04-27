#pragma once

#include "core/GameObject.hpp"

class Vest : public GameObject {
private:
	bool is_looking, has_activated;
public:
	Vest();

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};