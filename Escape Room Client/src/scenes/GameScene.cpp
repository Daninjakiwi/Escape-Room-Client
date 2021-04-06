#pragma once
#include "scenes/GameScene.hpp"

#include "core/Util.hpp"
#include "rooms/MurderMystery.hpp"

Room* GameScene::room = nullptr;
bool GameScene::ready = false;
std::string GameScene::msg = "";

void GameScene::StartUpListen(const std::string& message) {
	ready = true;
	msg = message;
}

void GameScene::Listen(const std::string& message) {

	room->ServerUpdate(message);
}

void GameScene::LoadRoom(Environment& env) {
	Json send;
	send.AddPair("action", "room_info");
	send.AddPair("code", env.code);
	send.AddPair("token", env.token);

	env.server->StopMessages();

	env.server->ListenForMessages(StartUpListen);

	env.server->Send(send);



	int attempts = 10;
	while (!ready && attempts > 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		attempts -= 1;
	}

	env.server->StopMessages();

	if (ready) {
		Json out = Util::JsonParse(msg);

		room = new MurderMystery(out.GetValue("state"));

		int i = 0;

		Json json;
		json.AddPair("action", "player_join");

		while (out.HasKey("player" + std::to_string(i))) {
			json.AddPair("username", out.GetValue("player") + std::to_string(i));
			room->ServerUpdate(json);
			i++;
		}


		send.AddPair("action", "join");
		env.server->ListenForMessages(Listen);
		env.server->Send(send);

		env.scene = Scene::Get("Game");
	}





}

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Update(Environment& env) {
	if (room) {
		room->LocalUpdate(env);
	}
	
}

void GameScene::Draw(volt::Window& window) {
	if (room) {
		room->Draw(window);
	}
}

