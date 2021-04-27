#pragma once

#include "core/GameObject.hpp"

class Note : public GameObject {
private:
	bool is_looking;
	bool has_activated;
	int type;
public:
	Note(int type);

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
};
