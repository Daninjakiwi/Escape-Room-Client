#pragma once

#include "core/GameObject.hpp"
#include "core/UniquePtr.hpp"

//Cardboard box
//0 = open small
//1 = flipped
//2 = closed wide
//3 = open wide (bugged verts - needs triangulation?)
//4 = tall closed

class CardboardBox : public GameObject {
private:
	static UniquePtr<volt::PbrMaterial> cardboard_material[3];
	static volt::Mesh cardboard_mesh[5];
public:
	CardboardBox(unsigned int type = 0, unsigned int quality = 0);
};
