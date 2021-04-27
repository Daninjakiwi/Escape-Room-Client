#pragma once
#include <Volt.hpp>

struct Hitbox {
public:
	volt::Vec3 size;
	volt::Vec3 position;
	bool disabled;

	Hitbox(volt::Vec3 position, volt::Vec3 size, bool disabled = false);
};
