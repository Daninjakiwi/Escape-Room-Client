#pragma once
#include "core/GameObject.hpp"

class Desk : public GameObject {
private:
	static UniquePtr<volt::PbrMaterial> materials[2];

	static volt::Mesh meshes[50];
protected:
	//0 = middle
	//1-4 = right (top-bottom)
	//5-8 = left (top-bottom)
	bool drawer_states[9];
public:
	Desk();
	virtual ~Desk() = default;

	void Draw(volt::Window& window);
	void SetDrawerState(int index, bool value);
};