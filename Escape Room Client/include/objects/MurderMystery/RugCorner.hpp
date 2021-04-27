#pragma once

#include "core/GameObject.hpp"

class RugCorner : public GameObject {
private:
	bool is_looking;
	bool moved;
public:
	RugCorner();

	void Update(Environment& env);
	void Draw(volt::Window& window);

	void OnLook();
};