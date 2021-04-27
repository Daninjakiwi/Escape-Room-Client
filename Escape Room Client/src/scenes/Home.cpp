#include "scenes/Home.hpp"
#include "core/Network.hpp"
#include "core/Util.hpp"

#include "scenes/GameScene.hpp"

bool Home::waiting = false;
std::string* Home::room_code = nullptr;



void JoinGameClick(Button* btn, Environment& env) {
	Home* scene = (Home*)env.scene;
	scene->code.getText();

	env.code = scene->code.getText();

	GameScene* game_scene = (GameScene*)Scene::Get("Game");
	game_scene->LoadRoom(env);
}

void Home::RecieveMessage(const std::string& msg) {
	Json json = Util::JsonParse((std::string&)msg);
	if (json.GetValue("status") == "success") {
		waiting = false;
		*room_code = json.GetValue("code");
	}
}

void HostClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("SelectScenario");

	/*
	Home* scene = (Home*)env.scene;

	Json data;
	data.AddPair("action", "host");
	data.AddPair("token", env.token);

	env.server->StopMessages();

	env.server->ListenForMessages(scene->RecieveMessage);

	env.server->Send(data);

	scene->waiting = true;

	scene->room_code = &env.code;

	int attempts = 20;
	while (scene->waiting && attempts > 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		attempts -= 1;
	}

	if (scene->waiting) {
		std::cout << "Something went wrong" << std::endl;
	}
	else {
		GameScene* game_scene = (GameScene*)Scene::Get("Game");

		game_scene->LoadRoom(env);

	


	}

	*/


}

void SettingsClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Settings");
}

void JoinClick(Button* btn, Environment& env);

void JoinCancel(Button* btn, Environment& env) {
	Home* scene = (Home*)env.scene;

	//scene->host = { scene->host.getText(), "width: 40%;height: 8%;left: 30%;bottom: 50%;text-align:center;text-size:auto 80%;" };
	scene->host.SetStyle("width: 40%;height: 8%;left: 30%;bottom: 45%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	

	if (scene->guest) {	
		scene->settings.SetStyle("width: 34%;height: 8%;left: 33%;bottom: 35%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	}
	else {
		scene->settings.SetStyle("width: 34%;height: 8%;left: 33%;bottom: 30%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	}

	scene->join.SetOnClick(JoinClick);

	//Set settings on click

	scene->show_code = false;
}

void JoinClick(Button* btn, Environment& env) {
	Home* scene = (Home*)env.scene;

	//scene->host = { scene->host.getText(), "width: 40%;height: 8%;left: 30%;bottom: 40%;text-align:center;text-size:auto 80%;" };

	scene->host.SetStyle("width: 40%;height: 8%;left: 30%;bottom: 30%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	if (scene->guest) {
		scene->settings.SetStyle("width: 34%;height: 8%;left: 33%;bottom: 20%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	}
	else {
		scene->settings.SetStyle("width: 34%;height: 8%;left: 33%;bottom: 15%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;");
	}
	

	scene->join.SetOnClick(JoinCancel);

	//Set settings on click


	scene->show_code = true;
}

Home::Home() : Scene(),
join("Join Room","width: 50%;height: 10%;left: 25%;bottom: 60%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
host("Host Room","width: 40%;height: 8%;left: 30%;bottom: 45%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
settings("Settings","width: 34%;height: 8%;left: 33%;bottom: 30%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
go("Join", "width: 8%;height: 6%;left: 59%;bottom: 46%;text-align:center;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
welcome("Welcome", "width: 30%;height: 5%;left: 1%;bottom: 94%;text-align:left;text-size:auto 80%;text-colour:#FFFFFF;colour:#00000000;"),
code("width: 25%;height: 8%;left: 33%;bottom: 45%;text-align:center;text-size: 48px;max-length: 10;text-colour:#FFFFFF;colour:#303030FF;","Code"),
show_code(false),
guest(false) {
	join.SetOnClick(JoinClick);
	host.SetOnClick(HostClick);
	go.SetOnClick(JoinGameClick);
	settings.SetOnClick(SettingsClick);
}

void Home::Update(Environment& env) {

	std::string& txt = (std::string&)welcome.getText();
	txt = "Welcome, " + env.username + "!";

	welcome.Update(env);

	join.Update(env);

	if (!guest) {
		host.Update(env);
	}

	
	settings.Update(env);

	if (show_code) {
		code.Update(env);
		go.Update(env);
	}
}

void Home::Draw(volt::Window& window) {
	join.Draw(window);

	welcome.Draw(window);

	if (!guest) {
		host.Draw(window);
	}
	
	settings.Draw(window);

	if (show_code) {
		code.Draw(window);
		go.Draw(window);
	}
}