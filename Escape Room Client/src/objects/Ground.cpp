#pragma once
#include "objects/Ground.hpp"

Ground::Ground(volt::Vec2 size) : GameObject() {
	_transform.scale = { size.x, 0.1f,size.y };
	_hitbox = new Hitbox(_transform.position, _transform.scale);
}