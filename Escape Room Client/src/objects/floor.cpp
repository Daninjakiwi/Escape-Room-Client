#include "objects/floor.hpp"

wall::wall(int width, int height) : GameObject(), base(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE)) {
	_mesh = &base;
	_transform.scale *= 5;
}