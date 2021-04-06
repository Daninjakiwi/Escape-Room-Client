#pragma once

#include "core/GameObject.hpp"

class wall : public GameObject {
private:
	volt::Mesh base;
public:
	wall(int width, int height);
};
