#include "objects/Cabinet.hpp"
#include "meshes/LoadMesh.hpp"

UniquePtr<volt::PbrMaterial> Cabinet::materials[2];

volt::Mesh Cabinet::meshes[11];

Cabinet::Cabinet() : GameObject(), drawer_states{ false,false } {
	if (!materials[0]) {
		materials[0].Init(new volt::PbrMaterial("resources/textures/pbr/wood/walnut"));
		materials[1].Init(new volt::PbrMaterial("resources/textures/pbr/metal/gold"));

		std::vector<volt::Mesh> model = Meshes::LoadSeperate("resources/meshes/cabinet.obj");

		for (int i = 0; i < 11; i++) {
			meshes[i] = model[i];
		}
	}
}

void Cabinet::Draw(volt::Window& window) {
	window.drawMesh(meshes[1], *materials[0], _transform);
	window.drawMesh(meshes[2], *materials[1], _transform);
	window.drawMesh(meshes[8], *materials[1], _transform);
	window.drawMesh(meshes[9], *materials[1], _transform);
	window.drawMesh(meshes[10], *materials[0], _transform);

	//MIDDLE CUBOARD

	if (drawer_states[0]) {
		Transform moved = _transform;
		moved.rotation.y -= 90.0f;
		moved.position.z += 1.5f;
		moved.position.x += 4.5f;
		window.drawMesh(meshes[6], *materials[1], moved);
		window.drawMesh(meshes[7], *materials[0], moved);
	}
	else {
		window.drawMesh(meshes[6], *materials[1],_transform);
		window.drawMesh(meshes[7], *materials[0],_transform);
	}

	//RIGHT CUBOARD
	if (drawer_states[1]) {
		Transform moved = _transform;
		moved.rotation.y += 90.0f;
		moved.position.z -= 7.7f;
		moved.position.x += 10.5f;
		window.drawMesh(meshes[3], *materials[1], moved);
		window.drawMesh(meshes[4], *materials[1], moved);
		window.drawMesh(meshes[5], *materials[0], moved);
	}
	else {
		window.drawMesh(meshes[3], *materials[1],_transform);
		window.drawMesh(meshes[4], *materials[1],_transform);
		window.drawMesh(meshes[5], *materials[0],_transform);
	}

}

void Cabinet::SetDrawerState(int index, bool state) {
	drawer_states[index % 2] = state;
}