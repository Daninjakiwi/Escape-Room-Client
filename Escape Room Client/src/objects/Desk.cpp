#include "objects/Desk.hpp"
#include "meshes/LoadMesh.hpp"

UniquePtr<volt::PbrMaterial> Desk::materials[2];

volt::Mesh Desk::meshes[50];

Desk::Desk() : GameObject(), drawer_states{false,false,false,false,false,false,false,false,false} {
	if (!materials[0]) {
		materials[0].Init(new volt::PbrMaterial("resources/textures/pbr/wood/walnut"));
		materials[1].Init(new volt::PbrMaterial("resources/textures/pbr/table_top"));

		std::vector<volt::Mesh> obj = Meshes::LoadSeperate("resources/meshes/desk.obj");

		for (int i = 0; i < 50; i++) {
			meshes[i] = obj[i];
		}
	}
}

void Desk::Draw(volt::Window& window) {
	Transform open = _transform;
	open.position.x += 0.25f * _transform.scale.x * (float)volt::maths::sind(_transform.rotation.y);
	open.position.z += 0.25f * _transform.scale.z * (float)volt::maths::cosd(_transform.rotation.y);

	window.drawMesh(meshes[0], *materials[0], _transform);
	window.drawMesh(meshes[1], *materials[0], _transform);
	window.drawMesh(meshes[2], *materials[1], _transform);

	//MIDDLE DRAW

	Transform used = drawer_states[0] ? open : _transform;
	window.drawMesh(meshes[13], *materials[0],used);
	window.drawMesh(meshes[14], *materials[0],used);
	window.drawMesh(meshes[15], *materials[1],used);
	window.drawMesh(meshes[16], *materials[1],used);
	window.drawMesh(meshes[30], *materials[1],used);

	//TOP RIGHT
	used = drawer_states[1] ? open : _transform;
	window.drawMesh(meshes[9], *materials[0],  used);
	window.drawMesh(meshes[10], *materials[0], used);
	window.drawMesh(meshes[11], *materials[1], used);
	window.drawMesh(meshes[12], *materials[1], used);

	//SECOND RIGHT
	used = drawer_states[2] ? open : _transform;
	window.drawMesh(meshes[35], *materials[0], used);
	window.drawMesh(meshes[36], *materials[0], used);
	window.drawMesh(meshes[37], *materials[1], used);
	window.drawMesh(meshes[3], *materials[1], used);

	//THIRD RIGHT
	used = drawer_states[3] ? open : _transform;
	window.drawMesh(meshes[4], *materials[0], used);
	window.drawMesh(meshes[5], *materials[0], used);
	window.drawMesh(meshes[6], *materials[1], used);
	window.drawMesh(meshes[7], *materials[1], used);

	//BOTTOM RIGHT
	used = drawer_states[4] ? open : _transform;
	window.drawMesh(meshes[38], *materials[0], used);
	window.drawMesh(meshes[39], *materials[0], used);
	window.drawMesh(meshes[40], *materials[1], used);
	window.drawMesh(meshes[8], *materials[1], used);

	//LEFT TOP
	used = drawer_states[5] ? open : _transform;
	window.drawMesh(meshes[26], *materials[0], used);
	window.drawMesh(meshes[28], *materials[0], used);
	window.drawMesh(meshes[27], *materials[1], used);
	window.drawMesh(meshes[29], *materials[1], used);

	//LEFT SECOND
	used = drawer_states[6] ? open : _transform;
	window.drawMesh(meshes[41], *materials[0], used);
	window.drawMesh(meshes[42], *materials[0], used);
	window.drawMesh(meshes[23], *materials[1], used);
	window.drawMesh(meshes[43], *materials[1], used);

	//LEFT THIRD
	used = drawer_states[7] ? open : _transform;
	window.drawMesh(meshes[44], *materials[0], used);
	window.drawMesh(meshes[45], *materials[0], used);
	window.drawMesh(meshes[24], *materials[1], used);
	window.drawMesh(meshes[46], *materials[1], used);

	//LEFT BOTTOM
	used = drawer_states[8] ? open : _transform;
	window.drawMesh(meshes[47], *materials[0], used);
	window.drawMesh(meshes[48], *materials[0], used);
	window.drawMesh(meshes[25], *materials[1], used);
	window.drawMesh(meshes[49], *materials[1], used);
}

void Desk::SetDrawerState(int index, bool value) {
	drawer_states[index % 9] = value;
}