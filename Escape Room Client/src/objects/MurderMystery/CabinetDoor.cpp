#pragma once

#include "objects/MurderMystery/CabinetDoor.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"

CabinetDoor::CabinetDoor(int index) : GameObject(), index(index), has_key(false), is_locked(false), is_open(false), looking(false) {
	if (index == 1) {
		is_locked = true;
	}
}

void CabinetDoor::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;

	MurderMystery* room = (MurderMystery*)scene->room;

	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	if (data->cabinet_key_found) {
		has_key = true;
	}

	if (data->cabinet_unlocked) {
		is_locked = false;
	}

	if (looking && env.window->isKeyJustPressed(volt::Keys::E)) {
		Json out;


		out.AddPair("action", "update");
		out.AddPair("token", env.token);
		out.AddPair("code", env.code);

		if (is_locked) {
			if (has_key) {
				out.AddPair("message", "unlock_cabinet");
				env.server->Send(out);
			}

		}
		else {
			if (is_open) {
				out.AddPair("message", "close_cabinet" + std::to_string(index));
				is_open = false;
				env.server->Send(out);
			}
			else {
				out.AddPair("message", "open_cabinet" + std::to_string(index));
				is_open = true;
				env.server->Send(out);
			}

		}
	}
}
void CabinetDoor::Draw(volt::Window& window) {
	if (looking) {
		lbl_name.setText("Cabinet");
		lbl_name.Draw(window);
		if (is_locked) {
			if (has_key) {
				lbl_action.setText("[E] Use Small Key");
				lbl_action.Draw(window, { 0.0f,1.0f,0.0f,1.0f });
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
void CabinetDoor::OnLook() {
	looking = true;
}