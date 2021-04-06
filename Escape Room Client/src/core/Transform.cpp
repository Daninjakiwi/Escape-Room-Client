#include "core/Transform.hpp"

Transform::Transform() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {

}

Transform::operator volt::Mat4() const {
	volt::Mat4 out(1.0f);
	out.scale(scale);
	out.rotate(rotation.x, { 1.0f,0.0f,0.0f });
	out.rotate(rotation.y, { 0.0f,1.0f,0.0f });
	out.rotate(rotation.z, { 0.0f,0.0f,1.0f });
	out.translate(position);

	return out;
}

