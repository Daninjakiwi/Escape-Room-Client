#pragma once
#include <Volt.hpp>
#include "Environment.hpp"
#include "Transform.hpp"
#include "Hitbox.hpp"
#include "core/UniquePtr.hpp"
#include "ui/Label.hpp"

class GameObject {
	friend class MurderMystery;
	friend class Player;
private:
	static volt::Mesh cube;
	static UniquePtr<volt::ColourMaterial> hitbox_material;
protected:
	volt::Material* _material;
	volt::Mesh* _mesh;
	static Label lbl_name, lbl_action;

public:
	Transform _transform;
	Hitbox* _hitbox;

	GameObject();
	virtual ~GameObject();

	void SetMaterial(volt::Material* material);
	void SetMesh(volt::Mesh* mesh);
	bool CollidesWith(GameObject& obj, bool ignore_disable = false);

	virtual void Update(Environment& env);
	virtual void Draw(volt::Window& window);
	virtual void OnLook();

	void DrawHitbox(volt::Window& window);
};
