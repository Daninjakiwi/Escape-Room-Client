#include "objects/MurderMystery/Safe.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"
#include "rooms/MurderMystery.hpp"
#include "meshes/LoadMesh.hpp"

UniquePtr<volt::PbrMaterial> Safe::materials[3];
volt::Mesh Safe::meshes[16];
bool Safe::is_active = false;
std::string Safe::combination = "";

void Safe::BtnSubmitClick(Button* btn, Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;

	Json send;
	send.AddPair("action", "update");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);
	send.AddPair("message", "open_safe" + combination);

	env.server->Send(send);

	combination = "";
}

void Safe::BtnCloseClick(Button* btn, Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;

	room->paused = false;
	is_active = false;
}

Safe::Safe() : GameObject(), is_open(false), is_looking(false), is_unlocked(false),
panel("width: 80%;height: 80%;left: 10%;bottom: 5%;colour:#303030AA;"),
btn_close("Close", "width: 10%;height: 8%;left: 11%;bottom: 76%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
btn_submit("Submit", "width: 10%;height: 10%;left: 45%;bottom: 10%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;") {
	if (!materials[0]) {
		materials[0].Init(new volt::PbrMaterial("resources/textures/pbr/metal/old_steel"));
		materials[1].Init(new volt::PbrMaterial("resources/textures/pbr/metal/silver"));
		materials[2].Init(new volt::PbrMaterial("resources/textures/pbr/keypad"));

		std::vector<volt::Mesh> model = Meshes::LoadSeperate("resources/meshes/safe.obj");
	
		for (int i = 0; i < 16; i++) {
			meshes[i] = model[i];
		}
	}
	_hitbox = new Hitbox({18.0f,0.0f,-33.5f}, {4.0f,1.0f,4.0f});
	btn_close.SetOnClick(BtnCloseClick);
	btn_submit.SetOnClick(BtnSubmitClick);
}

void Safe::Update(Environment& env) {
	GameScene* scene = (GameScene*)env.scene;
	MurderMystery* room = (MurderMystery*)scene->room;
	murder_mystery_data* data = (murder_mystery_data*)room->GetState();

	is_open = data->safe_open;
	is_unlocked = data->safe_unlocked;

	if (is_open && _hitbox) {
		delete _hitbox;
		_hitbox = nullptr;
	}

	if (is_looking) {
		if (env.window->isKeyJustPressed(volt::Keys::E)) {
			if (is_unlocked) {
				Json out;

				out.AddPair("action", "update");
				out.AddPair("token", env.token);
				out.AddPair("code", env.code);
				if (is_open) {
					//CLOSE
					out.AddPair("message", "close_safe");
				}
				else {
					out.AddPair("message", "open_safe");
				}
				env.server->Send(out);
			}
			else {
				//ENTER CODE
				room->paused = true;
				is_active = true;
			}
		}	
	}

	if (is_active) {
		if (data->safe_unlocked) {
			room->paused = false;
			is_active = false;
		}

		panel.Update(env);
		btn_close.Update(env);
		btn_submit.Update(env);
	}
}
void Safe::Draw(volt::Window& window) {
	if (is_looking) {
		lbl_name.setText("Safe");
		lbl_name.Draw(window);
		if (is_unlocked) {
			std::string type = is_open ? "Close" : "Open";

			lbl_action.setText("[E] " + type);
		}
		else {
			lbl_action.setText("[E] Enter Code");
		}
		lbl_action.Draw(window);
	}

	if (is_active) {
		panel.Draw(window);
		btn_close.Draw(window);
		btn_submit.Draw(window);

		std::string display = "";

		for (int i = 0; i < 4; i++) {
			if (combination.length() > i) {
				display += combination[i];
			}
			else {
				display += "_";
			}
			display += "    ";
		}

		window.drawString(display, { 510.0f, 550.0f }, 72, volt::fonts::SEGOE, { 1.0f,1.0f,1.0f,1.0f });

		volt::Vec4 col = { 0.1f,0.1f,0.1f,0.3f };

		for (int i = 0; i < 9; i++) {
			volt::Vec2 pos = { 545.0f + ((i % 3) * 80.0f) ,440.0f - ((i / 3) * 80.0f) };
			window.drawString(std::to_string(i+1), pos, 64, volt::fonts::SEGOE, { 1.0f,1.0f,1.0f,1.0f });

			if (window.getMousePos().x >= pos.x && window.getMousePos().x < pos.x + 80 && window.getMousePos().y >= pos.y && window.getMousePos().y < pos.y + 80) {
				volt::Quad box({pos.x - 32.0f, pos.y - 32.0f}, { 80.0f,80.0f }, col);
				window.drawQuad(box, SEPERATE);
				if (window.isMouseJustPressed()) {
					combination += std::to_string(i+1);
				}
			}
		}

		volt::Vec2 pos = { 545.0f + ((10 % 3) * 80.0f) ,440.0f - ((10 / 3) * 80.0f) };
		window.drawString("0", pos, 64, volt::fonts::SEGOE, { 1.0f,1.0f,1.0f,1.0f });

		if (window.getMousePos().x >= pos.x && window.getMousePos().x < pos.x + 80 && window.getMousePos().y >= pos.y && window.getMousePos().y < pos.y + 80) {
			volt::Quad box({ pos.x - 32.0f, pos.y - 32.0f }, { 80.0f,80.0f }, col);
			window.drawQuad(box, SEPERATE);
			if (window.isMouseJustPressed()) {
				combination += "0";
			}
		}

		pos = { 545.0f + (3.0f * 80.0f) ,440.0f };
		window.drawString("<-", pos, 64, volt::fonts::SEGOE, { 1.0f,1.0f,1.0f,1.0f });

		if (window.getMousePos().x >= pos.x && window.getMousePos().x < pos.x + 80 && window.getMousePos().y >= pos.y && window.getMousePos().y < pos.y + 80) {
			volt::Quad box({ pos.x - 32.0f, pos.y - 32.0f }, { 80.0f,80.0f }, col);
			window.drawQuad(box, SEPERATE);
			if (window.isMouseJustPressed()) {
				if (combination.length() > 0) {
					combination = combination.substr(0, combination.length() - 1);
				}
			}
		}

	}

	for (int i = 0; i < 3; i++) {
		window.drawMesh(meshes[i], *materials[0], _transform);
	}

	Transform t = _transform;

	if (is_open) {
		t.rotation.y = 110.0f;
		t.position.y += 4.5f;
		t.position.x += 0.5f;
	}

	window.drawMesh(meshes[3], *materials[0], t);

	window.drawMesh(meshes[8], *materials[0], t);	
	window.drawMesh(meshes[9], *materials[0], t);	
	window.drawMesh(meshes[10], *materials[0], t);	

	for (int i = 4; i < 8; i++) {
		window.drawMesh(meshes[i], *materials[1], t);
	}

	window.drawMesh(meshes[11], *materials[1], t);
	window.drawMesh(meshes[12], *materials[2], t);
	window.drawMesh(meshes[13], *materials[2], t);

	//4 = middle
	//5-6 spinner arms
	//7 outside spinner
	//10-13 = lock
	//13 = keypad
	
	is_looking = false;
}

void Safe::OnLook() {
	is_looking = true;
}