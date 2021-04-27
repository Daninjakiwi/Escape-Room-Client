#pragma once

#include "core/GameObject.hpp"
#include "core/UniquePtr.hpp"

class Door : public GameObject {
private:
	//Materials
		//0 = Main door
		//1 = Door handle
	static UniquePtr<volt::PbrMaterial> door_materials[2];

	//Meshes
		//0 = frame
		//1 = main door
		//2 = inner door
		//3 = handle
		//4 = keyway
	static volt::Mesh door_meshes[5];
protected:
	bool is_open;
	bool is_ready;
	bool is_looking;
	bool is_fixed;
public:
	Door();
	virtual ~Door();

	void Update(Environment& env);
	void Draw(volt::Window& window);

	void OnLook();

	void Open();
	void Close();

	bool IsOpen();
};