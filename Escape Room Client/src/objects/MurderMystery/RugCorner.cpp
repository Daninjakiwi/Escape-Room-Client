#pragma once

#include "objects/MurderMystery/RugCorner.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

RugCorner::RugCorner() : GameObject(), is_looking(false), moved(false) {
	_hitbox = new Hitbox({ 13.8f,0.0f,-39.0f }, { 1.5f,1.0f,1.5f });
}

void RugCorner::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	moved = data->carpet_moved;

	if (is_looking && env.window->isKeyJustPressed(volt::Keys::E) && !moved) {
		Json out;

		out.AddPair("action", "update");
		out.AddPair("token", env.token);
		out.AddPair("code", env.code);
		out.AddPair("message", "move_rug");
		env.server->Send(out);
	}

}

void RugCorner::Draw(volt::Window& window) {
	if (is_looking && !moved) {
		lbl_name.setText("Rug");
		lbl_name.Draw(window);

		lbl_action.setText("[E] Move");
		lbl_action.Draw(window);
		//window.drawString("Move rug", { 200.0f,200.0f }, 48, volt::fonts::SEGOE, { 1.0f,1.0f,1.0f,1.0f });
		is_looking = false;
	}
}

void RugCorner::OnLook() {
	is_looking = true;
}