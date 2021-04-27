#pragma once

#include "core/GameObject.hpp"

class Drill : public GameObject {
private:
	bool is_looking, has_activated;
public:
	Drill();

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};