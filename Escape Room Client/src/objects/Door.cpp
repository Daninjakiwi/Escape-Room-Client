#pragma once

#include "objects/Door.hpp"
#include "meshes/LoadMesh.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

UniquePtr<volt::PbrMaterial> Door::door_materials[2];
volt::Mesh Door::door_meshes[5];

Door::Door() : GameObject(), is_open(false), is_ready(false),is_looking(false), is_fixed(false) {
	if (!door_materials[0]) {
		door_materials[0].Init(new volt::PbrMaterial("resources/textures/pbr/wood/walnut"));
		door_materials[1].Init(new volt::PbrMaterial("resources/textures/pbr/metal/gold"));

		std::vector<volt::Mesh> temp = Meshes::LoadSeperate("resources/meshes/door.obj");
		for (int i = 0; i < 5; i++) {
			door_meshes[i] = temp[i];
		}
	}
	_transform.scale *= 13.0f;
}
Door::~Door() {

}

void Door::OnLook() {
	is_looking = true;
}

void Door::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	is_fixed = data->door_fixed;
	is_ready = data->drill_found && data->screws_found;
	is_open = data->door_open;

	if (is_open) {
		_hitbox->disabled = true;
	}

	if (is_looking && env.window->isKeyJustPressed(volt::Keys::E)) {
		if (is_ready && !is_fixed) {
			//FIX
			Json send;
			send.AddPair("action", "update");
			send.AddPair("token", env.token);
			send.AddPair("code", env.code);
			send.AddPair("message", "fix_door");

			env.server->Send(send);
		}
		else if (is_fixed) {
			//OPEN
			Json send;
			send.AddPair("action", "update");
			send.AddPair("token", env.token);
			send.AddPair("code", env.code);
			send.AddPair("message", "open_door");

			env.server->Send(send);
		}
	}
}

void Door::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Door");
		lbl_name.Draw(window);

		if (!is_fixed) {
			if (!is_ready) {
				lbl_action.setText("Fix (Missing Items)");
				lbl_action.Draw(window, { 1.0f,0.0f,0.0f,1.0f });
			}
			else {
				lbl_action.setText("[E] Fix");
				lbl_action.Draw(window, { 0.0f,1.0f,0.0f,1.0f });
			}
		}
		else {
			if (!is_open) {
				lbl_action.setText("[E] Open");
				lbl_action.Draw(window);
			}
		}
	}

	window.drawMesh(door_meshes[0], *door_materials[0], _transform);

	if (is_open) {
		Transform temp = _transform;
		temp.rotation.y += 90.0f;
		temp.position.x += 0.08f * _transform.scale.x;
		temp.position.z -= 0.08f * _transform.scale.z;

		window.drawMesh(door_meshes[1], *door_materials[0], temp);
		window.drawMesh(door_meshes[2], *door_materials[0], temp);
		window.drawMesh(door_meshes[3], *door_materials[1], temp);
		window.drawMesh(door_meshes[4], *door_materials[1], temp);
	}
	else {
		window.drawMesh(door_meshes[1], *door_materials[0], _transform);
		window.drawMesh(door_meshes[2], *door_materials[0], _transform);

		if (!is_fixed) {
			Transform temp = _transform;
			temp.rotation.x += 30.0f;
			temp.position.z -= 4.5f;
			temp.position.y += 1.5f;
			window.drawMesh(door_meshes[3], *door_materials[1], temp);
			window.drawMesh(door_meshes[4], *door_materials[1], temp);
		}
		else {
			window.drawMesh(door_meshes[3], *door_materials[1], _transform);
			window.drawMesh(door_meshes[4], *door_materials[1], _transform);
		}

		
	}

	is_looking = false;



}

void Door::Open() {
	is_open = true;
}
void Door::Close() {
	is_open = false;
}

bool Door::IsOpen() {
	return is_open;
}