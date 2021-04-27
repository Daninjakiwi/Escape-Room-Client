#include "objects/MurderMystery/Drill.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"


Drill::Drill() : GameObject(), is_looking(false), has_activated(false) {
	_hitbox = new Hitbox({19.8f,-2.3f,-34.0f}, {2.0f,0.5f,2.0f});
}

void Drill::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	has_activated = data->drill_found;

	if (is_looking && !has_activated && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json send;
		send.AddPair("action", "update");
		send.AddPair("token", env.token);
		send.AddPair("code", env.code);
		send.AddPair("message", "add_drill");

		env.server->Send(send);
	}
}

void Drill::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Drill");
		lbl_name.Draw(window);

		if (!has_activated) {
			lbl_action.setText("[E] Take");
			lbl_action.Draw(window);
		}
		is_looking = false;
	}
}

void Drill::OnLook() {
	is_looking = true;
}
