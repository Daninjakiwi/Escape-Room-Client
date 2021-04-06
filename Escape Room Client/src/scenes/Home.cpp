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

	std::cout << "joining room" << std::endl;

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
	Home* scene = (Home*)env.scene;

	Json data;
	data.AddPair("action", "host");
	data.AddPair("token", env.token);

	//UdpConnection server = Network::UdpConnect(env.ip, env.port);

	env.server->StopMessages();

	env.server->ListenForMessages(scene->RecieveMessage);

	//server.ListenForMessages(scene->RecieveMessage);

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
		std::cout << "Joining room " << env.code << std::endl;
		GameScene* game_scene = (GameScene*)Scene::Get("Game");
		game_scene->LoadRoom(env);


	}

}

void SettingsClick(Button* btn, Environment& env) {

}

void JoinClick(Button* btn, Environment& env);

void JoinCancel(Button* btn, Environment& env) {
	Home* scene = (Home*)env.scene;

	scene->host = { scene->host.getText(), "width: 40%;height: 8%;left: 30%;bottom: 50%;text-align:center;text-size:auto 80%;" };
	

	if (scene->guest) {
		scene->settings = { scene->settings.getText(), "width: 34%;height: 8%;left: 33%;bottom: 50%;text-align:center;text-size:auto 80%;" };
	}
	else {
		scene->settings = { scene->settings.getText(), "width: 34%;height: 8%;left: 33%;bottom: 40%;text-align:center;text-size:auto 80%;" };
	}

	scene->join.SetOnClick(JoinClick);

	//Set settings on click

	scene->host.SetOnClick(HostClick);

	scene->show_code = false;
}

void JoinClick(Button* btn, Environment& env) {
	Home* scene = (Home*)env.scene;

	scene->host = { scene->host.getText(), "width: 40%;height: 8%;left: 30%;bottom: 40%;text-align:center;text-size:auto 80%;" };

	if (scene->guest) {
		scene->settings = { scene->settings.getText(), "width: 34%;height: 8%;left: 33%;bottom: 40%;text-align:center;text-size:auto 80%;" };
	}
	else {
		scene->settings = { scene->settings.getText(), "width: 34%;height: 8%;left: 33%;bottom: 30%;text-align:center;text-size:auto 80%;" };
	}
	

	scene->join.SetOnClick(JoinCancel);

	//Set settings on click

	scene->host.SetOnClick(HostClick);

	scene->show_code = true;
}

Home::Home() : Scene(),
join("Join Room","width: 50%;height: 10%;left: 25%;bottom: 60%;text-align:center;text-size:auto 80%"),
host("Host Room","width: 40%;height: 8%;left: 30%;bottom: 50%;text-align:center;text-size:auto 80%;"),
settings("Settings","width: 34%;height: 8%;left: 33%;bottom: 40%;text-align:center;text-size:auto 80%;"),
go("Join", "width: 8%;height: 6%;left: 59%;bottom: 51%;text-align:center;text-size:auto 80%;"),
code("width: 25%;height: 8%;left: 33%;bottom: 50%;text-align:center;text-size: 48px;max-length: 10;",""),
show_code(false),
guest(false) {
	join.SetOnClick(JoinClick);
	host.SetOnClick(HostClick);
	go.SetOnClick(JoinGameClick);
}

void Home::Update(Environment& env) {
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

	if (!guest) {
		host.Draw(window);
	}
	
	settings.Draw(window);

	if (show_code) {
		code.Draw(window);
		go.Draw(window);
	}
}