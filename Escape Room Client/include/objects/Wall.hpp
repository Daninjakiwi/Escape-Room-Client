#pragma once

#include "core/GameObject.hpp"

class Wall : public GameObject {
public:
	Wall(volt::Vec3 size, volt::Vec3 position);
};
