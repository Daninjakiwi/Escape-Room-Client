#include <iostream>
#include <Volt.hpp>

#include "scenes/GameScene.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/Login.hpp"
#include "scenes/CreateAccount.hpp"
#include "scenes/Home.hpp"
#include "scenes/SelectScenario.hpp"
#include "scenes/Settings.hpp"
#include "scenes/Credits.hpp"

#include "core/Network.hpp"

int main() {

	int fps = 0;
	int ms = 0;
	double delta_total = 0.0;
	bool show_info = false;

	Network::Initialise();

	volt::Window window("Escape Room", {});

	window.createContext(volt::ContextType::OPENGL);

	window.setBackgroundColour({0.1f,0.1f,0.1f,1.0f });

	window.loadEnvironmentMap("resources/textures/street.hdr");

	volt::DynamicTexture::setQuality(volt::Quality::ULTRA);

	Label lbl_info("", "width:fit;height: 8%;left: 1%;bottom: 90%;colour:#191919AA;text-colour:#FFFFFF;text-size:0.06h;text-align:center;");

	MainMenu main_menu_scene;
	GameScene game_scene;
	Login login_scene;
	CreateAccount create_account_scene;
	Home home_scene;
	SelectScenario select_scenario_scene(window);
	Settings settings;
	Credits credits;

	Scene::Register("MainMenu", &main_menu_scene);
	Scene::Register("Game", &game_scene);
	Scene::Register("Login", &login_scene);
	Scene::Register("CreateAccount", &create_account_scene);
	Scene::Register("Home", &home_scene);
	Scene::Register("SelectScenario", &select_scenario_scene);
	Scene::Register("Settings", &settings);
	Scene::Register("Credits", &credits);

	Environment env;
	env.server = new UdpConnection("0.0.0.0", 0); 

	env.window = &window;
	env.scene = Scene::Get("MainMenu");

	while (window) {
		if (window.isKeyJustPressed(volt::Keys::M)) {
			show_info = !show_info;
		}

		((Scene*)env.scene)->Update(env);
		((Scene*)env.scene)->Draw(window);

		if (show_info) {
			lbl_info.setText("fps: " + std::to_string(fps) + " (" + std::to_string(ms) + "ms)");
			lbl_info.Update(env);
			lbl_info.Draw(window);
		}


		window.update();

		if (window.getDelta() >= 0) {
			delta_total += window.getDelta();
		}

		if (delta_total >= 0.4) {
			delta_total = 0.0;
			fps = 1.0 / window.getDelta();
			ms = window.getDelta() * 1000.0;
		}
	}

	Network::Terminate();

	
}