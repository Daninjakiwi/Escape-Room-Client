#include "core/GameObject.hpp"

GameObject::GameObject() : _material(nullptr), _mesh(nullptr), _hitbox(nullptr) {

}

GameObject::~GameObject() {

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
	window.drawMesh(*_mesh, *_material, _transform);
}