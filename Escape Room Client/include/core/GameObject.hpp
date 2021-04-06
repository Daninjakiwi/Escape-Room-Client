#pragma once
#include <Volt.hpp>
#include "Environment.hpp"
#include "Transform.hpp"
#include "Hitbox.hpp"

class GameObject {
	friend class MurderMystery;
	friend class Player;
protected:
	volt::Material* _material;
	volt::Mesh* _mesh;
	Transform _transform;
	Hitbox* _hitbox;
public:
	GameObject();
	virtual ~GameObject();

	void SetMaterial(volt::Material* material);
	void SetMesh(volt::Mesh* mesh);
	bool CollidesWith(GameObject& obj);

	virtual void Update(Environment& env);
	virtual void Draw(volt::Window& window);
	virtual void OnLook();
};
