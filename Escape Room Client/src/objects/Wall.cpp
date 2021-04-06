#include "objects/Wall.hpp"
#include "scenes/GameScene.hpp"


Wall::Wall(volt::Vec3 size, volt::Vec3 position) : GameObject() {
	_transform.scale = size;
	_transform.position = position;
	_hitbox = new Hitbox(_transform.position, _transform.scale);
}
