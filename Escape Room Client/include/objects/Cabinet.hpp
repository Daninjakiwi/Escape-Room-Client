#pragma once

#include "core/GameObject.hpp"
#include "core/UniquePtr.hpp"

class Cabinet : public GameObject {
private:
	static UniquePtr<volt::PbrMaterial> materials[2];
	static volt::Mesh meshes[11];

	bool drawer_states[2];
public:
	Cabinet();

	void Draw(volt::Window& window);
	void SetDrawerState(int index, bool state);
};