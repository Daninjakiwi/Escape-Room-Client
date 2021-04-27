#include "scenes/SelectScenario.hpp"
#include "scenes/Home.hpp"
#include "core/Util.hpp"
#include "scenes/GameScene.hpp"

std::vector<bool> available = { true, false,false };
std::vector<std::string> SelectScenario::scenarios = { "Crime Scene","Prison Break","Double Agent" };

const float width_total = 0.8f;
float size;
float gap;

void SelectScenario::BtnBackClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Home");
}

void SelectScenario::btn_click(Button* btn, Environment& env) {
	SelectScenario* scene = (SelectScenario*)env.scene;

	for (int i=0;i<scene->buttons.size();i++) {
		if (btn == scene->buttons[i]) {

			env.scene = Scene::Get("Home");

			Home* temp_scene = (Home*)env.scene;

			Json data;
			data.AddPair("action", "host");
			data.AddPair("token", env.token);

			env.server->StopMessages();

			env.server->ListenForMessages(temp_scene->RecieveMessage);

			env.server->Send(data);

			temp_scene->waiting = true;

			temp_scene->room_code = &env.code;

			int attempts = 20;
			while (temp_scene->waiting && attempts > 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				attempts -= 1;
			}

			if (temp_scene->waiting) {
				std::cout << "Something went wrong" << std::endl;
				env.scene = Scene::Get("SelectScenario");
			}
			else {
				GameScene* game_scene = (GameScene*)Scene::Get("Game");

				game_scene->LoadRoom(env);
			}
			break;
		}
	}
}

SelectScenario::SelectScenario(volt::Window& window) :
btn_back("Back", "width: 10%;height: 8%;left: 1%;bottom: 90%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;") {
	std::string longest;
	for (auto str : scenarios) {
		if (str.length() > longest.length()) {
			longest = str;
		}
	}

	btn_back.SetOnClick(BtnBackClick);

	float split = width_total * 100.0f / scenarios.size();

	size = ((int)floorf(split - 5.1f) + (5 - ceil((int)floorf(split - 5.1f) % 5))) / 100.0f;

	gap = (width_total - (size * scenarios.size())) / (scenarios.size() - 1);

	for (int i = 0; i < scenarios.size(); i++) {
		std::string style;
		style += "left:" + std::to_string(100.0f * (((1.0f - width_total) / 2.0f) + ((gap + size) * i))) + "%;";
		style += "bottom:30%;";
		style += "width:" + std::to_string(size * 100.0f) + "%;";
		style += "height:width 120%;";
		style += "text-align:center-top;";
		style += "text-size:auto 80%;";
		style += "colour:#19191901;";
		style += "text-colour:#FFFFFF;";
		style += "hover text-colour:#1286A8;";
		style += "text-facade:" + longest + ";";

		Button* btn = new Button(scenarios[i], style);
		buttons.emplace_back(btn);

		tex.emplace_back(new volt::Texture());



		if (available[i]) {
			btn->SetOnClick(btn_click);
			tex[i]->init("resources/textures/thumbnails/" + scenarios[i] + ".png");
		}
		else {
			tex[i]->init("resources/textures/thumbnails/unavailable.png");
		}


	}
}

SelectScenario::~SelectScenario() {
	for (auto btn : buttons) {
		delete btn;
	}

	for (auto t : tex) {
		delete t;
	}

}

void SelectScenario::Update(Environment& env) {
	for (auto btn : buttons) {
		btn->Update(env);
	}

	btn_back.Update(env);
}

void SelectScenario::Draw(volt::Window& window) {
	
	btn_back.Draw(window);

	for (int i = 0; i < scenarios.size(); i++) {
		window.drawTexture(*tex[i], { (((float)window.getSize().x) * (((1.0f - width_total) / 2.0f) + ((size + gap) * i))), ((float)window.getSize().y) * 0.3f }, { (float)window.getSize().x * size, (float)window.getSize().x * size });
	}

	for (auto btn : buttons) {
		btn->Draw(window);
	}




	
}