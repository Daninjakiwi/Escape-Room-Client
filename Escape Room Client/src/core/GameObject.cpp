#include "core/GameObject.hpp"

GameObject::GameObject() : _material(nullptr), _mesh(nullptr), _hitbox(nullptr) {

}

GameObject::~GameObject() {
	if (_hitbox) {
		delete _hitbox;
	}
}

void GameObject::SetMaterial(volt::Material* material) {
	_material = material;
}

void GameObject::SetMesh(volt::Mesh* mesh) {
	_mesh = mesh;
}

void GameObject::Update(Environment& env) {
}

void GameObject::Draw(volt::Window& window) {
	//Transform temp;
	//temp.position = _hitbox->position;
	//temp.scale = _hitbox->size;
	window.drawMesh(*_mesh, *_material, _transform);
}

void GameObject::OnLook() {
	std::cout << this << std::endl;
}

bool GameObject::CollidesWith(GameObject& obj) {
	if (_hitbox != nullptr && obj._hitbox != nullptr) {
		if ((_hitbox->position.x >= obj._hitbox->position.x && _hitbox->position.x <= obj._hitbox->position.x + obj._hitbox->size.x) || (obj._hitbox->position.x >= _hitbox->position.x && obj._hitbox->position.x <= _hitbox->position.x + _hitbox->size.x)) {
			if ((_hitbox->position.y >= obj._hitbox->position.y && _hitbox->position.y <= obj._hitbox->position.y + obj._hitbox->size.y) || (obj._hitbox->position.y >= _hitbox->position.y && obj._hitbox->position.y <= _hitbox->position.y + _hitbox->size.y)) {
				if ((_hitbox->position.z >= obj._hitbox->position.z - obj._hitbox->size.z && _hitbox->position.z <= obj._hitbox->position.z) || (_hitbox->position.z - _hitbox->size.z >= obj._hitbox->position.z - obj._hitbox->size.z && _hitbox->position.z - _hitbox->size.z <= obj._hitbox->position.z)) {
					return true;
				}

			}

		}
	}
	return false;
}