#pragma once
#include <util/maths/Vector.hpp>

namespace volt {
	struct Light {
		Vec3 position;
		Vec3 intensity;

		Light(Vec3 position, Vec3 intensity) : position(position), intensity(intensity) {};
	};
}
