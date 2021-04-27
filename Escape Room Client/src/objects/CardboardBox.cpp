#pragma once

#include "objects/CardboardBox.hpp"
#include "meshes/LoadMesh.hpp"

UniquePtr<volt::PbrMaterial> CardboardBox::cardboard_material[3];
volt::Mesh CardboardBox::cardboard_mesh[5];

CardboardBox::CardboardBox(unsigned int type, unsigned int quality) {
	if (!cardboard_material[0]) {
		cardboard_material[0].Init(new volt::PbrMaterial("resources/textures/pbr/cardboard/normal"));
		cardboard_material[1].Init(new volt::PbrMaterial("resources/textures/pbr/cardboard/worn"));
		cardboard_material[2].Init(new volt::PbrMaterial("resources/textures/pbr/cardboard/damaged"));

		cardboard_mesh[0] = Meshes::Load("resources/meshes/cardboard_box1.obj");
		cardboard_mesh[1] = Meshes::Load("resources/meshes/cardboard_box2.obj");
		cardboard_mesh[2] = Meshes::Load("resources/meshes/cardboard_box3.obj");
		cardboard_mesh[3] = Meshes::Load("resources/meshes/cardboard_box4.obj");
		cardboard_mesh[4] = Meshes::Load("resources/meshes/cardboard_box5.obj");
	}
	_material = cardboard_material[quality];
	_mesh = &cardboard_mesh[type];

	_transform.scale *= 0.05f;
}