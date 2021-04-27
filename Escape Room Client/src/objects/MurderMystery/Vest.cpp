#pragma once
#include "objects/MurderMystery/Vest.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

Vest::Vest() : GameObject(), is_looking(false), has_activated(false) {
	_hitbox = new Hitbox({ 39.5f,8.5f,-1.5f }, {2.5f,3.5f,1.0f});
}

void Vest::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	has_activated = data->screws_found;

	if (is_looking && !has_activated && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json send;
		send.AddPair("action", "update");
		send.AddPair("token", env.token);
		send.AddPair("code", env.code);
		send.AddPair("message", "add_screws");

		env.server->Send(send);
	}
}

void Vest::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Vest");
		lbl_name.Draw(window);

		if (!has_activated) {
			lbl_action.setText("[E] Search");
			lbl_action.Draw(window);
		}

		is_looking = false;
	}
}

void Vest::OnLook() {
	is_looking = true;
}

