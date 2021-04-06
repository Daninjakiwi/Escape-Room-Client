#pragma once
#include <Volt.hpp>

struct Transform {
	volt::Vec3 position;
	volt::Vec3 rotation;
	volt::Vec3 scale;

	Transform();

	operator volt::Mat4() const;
};
