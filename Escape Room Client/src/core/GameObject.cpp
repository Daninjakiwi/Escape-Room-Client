#include "core/GameObject.hpp"

volt::Mesh GameObject::cube = volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE);
UniquePtr<volt::ColourMaterial> GameObject::hitbox_material;
Label GameObject::lbl_name("", "width:fit;height: 8%;left:center;bottom: 90%;colour:#191919AA;text-colour:#FFFFFF;text-size:0.08h;text-align:center;");
Label GameObject::lbl_action("", "width:fit;height: 8%;left:center;bottom: 25%;colour:#191919AA;text-colour:#FFFFFF;text-size:0.07h;text-align:center;");

GameObject::GameObject() : _material(nullptr), _mesh(nullptr), _hitbox(nullptr) {
	if (!hitbox_material) {
		hitbox_material.Init(new volt::ColourMaterial({ 0.0f,0.0f,1.0f,0.5f }));
	}
}

GameObject::~GameObject() {
	if (_hitbox) {
		delete _hitbox;
	}
}

void GameObject::SetMaterial(volt::Material* material) {
	_material = material;
}

void GameObject::DrawHitbox(volt::Window& window) {
	if (_hitbox) {
		Transform t;
		t.position = _hitbox->position;
		t.scale = _hitbox->size;
		window.drawMesh(cube, *hitbox_material, t);
	}

}

void GameObject::SetMesh(volt::Mesh* mesh) {
	_mesh = mesh;
}

void GameObject::Update(Environment& env) {
}

void GameObject::Draw(volt::Window& window) {
	if (_mesh && _material) {
		window.drawMesh(*_mesh, *_material, _transform);
	}
	

	
}

void GameObject::OnLook() {
}

bool GameObject::CollidesWith(GameObject& obj, bool ignore_disable) {
	if (_hitbox != nullptr && obj._hitbox != nullptr) {
		if (!ignore_disable && obj._hitbox->disabled) {
			return false;
		}
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