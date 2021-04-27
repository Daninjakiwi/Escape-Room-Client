#include "objects/Drawer.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

Drawer::Drawer(int index) : GameObject(), has_key(false), index(index), locked(false), is_open(false), looking(false) {
	//ADD HITBOX
	if (index == 0) {
		locked = true;
	}
}

void Drawer::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;

	MurderMystery* room = (MurderMystery*)scene->room;

	murder_mystery_data* data = (murder_mystery_data*)room->GetState();


	has_key = data->desk_key_found;

	if (data->desk_unlocked) {
		locked = false;
	}

	if (looking && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json out;


		out.AddPair("action", "update");
		out.AddPair("token", env.token);
		out.AddPair("code", env.code);

		if (locked) {
			if (has_key) {
				out.AddPair("message", "unlock_desk");
				env.server->Send(out);
			}

		}
		else {
			if (is_open) {
				out.AddPair("message", "close_drawer" + std::to_string(index));
				is_open = false;
				env.server->Send(out);
			}
			else {
				out.AddPair("message", "open_drawer" + std::to_string(index));
				is_open = true;
				env.server->Send(out);
			}
			
		}

		

		

		
	}
}
void Drawer::Draw(volt::Window& window) {

	if (looking) {
		lbl_name.setText("Drawer");
		lbl_name.Draw(window);
		if (locked) {
			if (has_key) {
				lbl_action.setText("[E] Unlock");
				lbl_action.Draw(window, {0.0f,1.0f,0.0f,1.0f});
			}
			else {
				lbl_action.setText("Locked (Missing Key)");
				lbl_action.Draw(window, { 1.0f,0.0f,0.0f,1.0f });
			}
		}
		else {
			std::string str = is_open ? "Close" : "Open";
		
			lbl_action.setText("[E] " + str);
			lbl_action.Draw(window);
		}
		
	}

	looking = false;
}
void Drawer::OnLook() {
	looking = true;
}