#pragma once
#include "objects/MurderMystery/Chest.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"


bool Chest::is_active = false;
std::string Chest::combination = "";

void Chest::BtnCloseClick(Button* btn, Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;

	room->paused = false;
	is_active = false;
}

void Chest::BtnLeftClick(Button* btn, Environment& env) {
	combination += "l";

	Json send;
	send.AddPair("action", "update");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);
	send.AddPair("message", "open_chest" + combination);

	env.server->Send(send);
}

void Chest::BtnRightClick(Button* btn, Environment& env) {
	combination += "r";

	Json send;
	send.AddPair("action", "update");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);
	send.AddPair("message", "open_chest" + combination);

	env.server->Send(send);
}


Chest::Chest() : GameObject(), is_looking(false),
panel("width: 80%;height: 80%;left: 10%;bottom: 5%;colour:#303030AA;"),
btn_close("Close","width: 10%;height: 8%;left: 11%;bottom: 76%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
btn_left("Turn left", "width: 12%;height:10%;left: 21%;bottom: 35%;text-align:center;text-size:0.06h;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
btn_right("Turn right", "width: 12%;height:10%;left: 66%;bottom: 35%;text-align:center;text-size:0.06h;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
lbl_info("The key appears to be stuck. It can only be turned left or right.", "width: 70%;height: 30%;left: 15%;bottom: 55%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;"),
tex_chest("resources/textures/thumbnails/chest.png") {
	_hitbox = new Hitbox({40.0f,4.5f,-28.0f}, {1.2f,0.5f,1.2f}, true);
	btn_close.SetOnClick(BtnCloseClick);
	btn_left.SetOnClick(BtnLeftClick);
	btn_right.SetOnClick(BtnRightClick);
}

void Chest::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	if (is_looking && env.window->isKeyJustPressed(volt::Keys::E)) {
		room->paused = true;
		is_active = true;
		combination = "";
	}

	if (is_active) {
		if (data->chest_open) {
			room->paused = false;
			is_active = false;
		}

		panel.Update(env);
		btn_close.Update(env);
		btn_left.Update(env);
		btn_right.Update(env);
		lbl_info.Update(env);
	}
}

void Chest::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Chest");
		lbl_name.Draw(window);

		lbl_action.setText("[E] Open");
		lbl_action.Draw(window);

		is_looking = false;
	}

	if (is_active) {
		panel.Draw(window);
		btn_close.Draw(window);
		btn_left.Draw(window);
		btn_right.Draw(window);
		lbl_info.Draw(window);

		volt::iVec2 size = window.getSize();

		window.drawTexture(tex_chest, {size.width * 0.345f,size.height * 0.15f}, {size.width * 0.3f,size.width * 0.3f});
	}
}

void Chest::OnLook() {
	is_looking = true;
}
