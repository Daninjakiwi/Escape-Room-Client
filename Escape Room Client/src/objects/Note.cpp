#include "objects/Note.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

Note::Note(int type) : GameObject(), is_looking(false), has_activated(false), type(type) {

}

void Note::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	has_activated = data->note_found[type];

	if (is_looking && !has_activated && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json send;
		send.AddPair("action", "update");
		send.AddPair("token", env.token);
		send.AddPair("code", env.code);
		send.AddPair("message", "add_note_" + std::to_string(type));

		env.server->Send(send);
	}

}
void Note::Draw(volt::Window& window) {
	if (is_looking && !has_activated) {
		lbl_name.setText("Note");
		lbl_name.Draw(window);
		lbl_action.setText("[E] Take");
		lbl_action.Draw(window);

		is_looking = false;
	}
	
}
void Note::OnLook() {
	is_looking = true;
}