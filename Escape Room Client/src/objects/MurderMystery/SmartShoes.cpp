#include "objects/MurderMystery/SmartShoes.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

SmartShoes::SmartShoes() :GameObject(), has_activated(false), is_looking(false) {
	_hitbox = new Hitbox({45.0f,5.0f,-10.5f}, { 2.0f,2.0f,2.0f });
}

void SmartShoes::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	has_activated = data->desk_key_found;

	if (is_looking && !has_activated && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json send;
		send.AddPair("action", "update");
		send.AddPair("token", env.token);
		send.AddPair("code", env.code);
		send.AddPair("message", "add_desk_key");

		env.server->Send(send);
	}
}

void SmartShoes::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Smart Shoes");
		lbl_name.Draw(window);
		if (!has_activated) {
			lbl_action.setText("[E] Search");
			lbl_action.Draw(window);
		}
	}
	is_looking = false;
}

void SmartShoes::OnLook() {
	is_looking = true;
}