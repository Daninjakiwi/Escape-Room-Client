#pragma once

#include "rooms/Room.hpp"
#include <ctime>
#include <sstream>
#include <algorithm>

void make_anouncement(const std::string& message, unsigned int duration, std::string* output) {
	*output = message;
	std::this_thread::sleep_for(std::chrono::seconds(duration));
	*output = "";
}

Room::Room(const std::string& data, unsigned int byte_count, int min_players, int max_players) : byte_count(byte_count), state(nullptr),
announcement("", "width:fit;height: 6%;left:1%;bottom: 92%;text-align:left;colour:#191919AA;text-size:0.06h;text-colour:#FFFFFF;"),
timer("--:--","width: 10%;height: 5%;left: 88%;bottom: 93%;text-align:center;colour:#191919AA;text-size:auto 70%;text-colour:#FFFFFF;"), min_players(min_players), max_players(max_players), menu_open(false), inventory_open(false), paused(false) {
	state = malloc(byte_count);

	if (state) {
		memcpy(state, data.data(), byte_count);
	}
}

Room::~Room() {
	for (auto obj : objects) {
		delete obj.second;
	}

	for (auto mesh : meshes) {
		delete mesh.second;
	}

	for (auto mat : materials) {
		delete mat.second;
	}

	for (auto it = players.begin(); it < players.end(); it++) {
		delete *it;
	}
}

void Room::LocalUpdate(Environment& env) {
	int size = message_queue.size();
	for (int i = 0; i < size; i++) {
		Json& message = message_queue[i];
		if (message.GetValue("action") == "room_update") {
			memcpy(state, message.GetValue("state").data(), byte_count);
		}
		else if (message.GetValue("action") == "player_join") {
			//players.push_back(recieve.GetValue("username"));
			Player* p = new Player(message.GetValue("username"));
			p->SetMesh(meshes["player"]);
			p->SetMaterial(materials["player"]);

			players.push_back(p);

			//MakeAnnouncement(message.GetValue("username") + " joined.", 5);
		}
		else if (message.GetValue("action") == "player_update") {
			if (username != message.GetValue("username")) {
				for (auto it = players.begin(); it < players.end(); it++) {
					if ((*it)->name == message.GetValue("username")) {
						(*it)->_transform.position = Util::StringToVector(message.GetValue("position"));
						(*it)->_hitbox->position = Util::StringToVector(message.GetValue("position"));

						(*it)->_transform.rotation.y = Util::StringToVector(message.GetValue("rotation")).y;
						break;
					}
				}
			}
		}
	}

	std::vector<decltype(message_queue)::value_type>(message_queue.begin() + size, message_queue.end()).swap(message_queue);

	reserved_state* data = (reserved_state*)state;
	
	if (announcement.getText() != "") {
		announcement.Update(env);
		
	}

	if (data->playing) {

		long long remaining = data->end_time - std::time(nullptr);
		if (remaining < 0) {
			//End  game
		}
		else {
			unsigned int minutes = remaining / ((long long)60);
			unsigned int seconds = remaining - ((long long)minutes * 60);

			std::string& str = (std::string&)timer.getText();

			std::string str_minutes = std::to_string(minutes);
			std::string str_seconds = std::to_string(seconds);

			if (str_minutes.length() < 2) {
				str_minutes.insert(0, 2 - str_minutes.length(), '0');
			}

			if (str_seconds.length() < 2) {
				str_seconds.insert(0, 2 - str_seconds.length(), '0');
			}

			str = str_minutes + ":" + str_seconds;
		}
	}

	timer.Update(env);






}

void Room::Draw(volt::Window& window) {
	reserved_state* data = (reserved_state*)state;

	if (data->playing) {
		timer.Draw(window);

		if (!paused) {

			volt::Quad q({ (window.getSize().x / 2) - 2.0f, (window.getSize().y / 2) - 2.0f }, { 4.0f,4.0f }, { 1.0f,1.0f,0.0f,1.0f });

			window.drawQuad(q, SEPERATE);
		}

	}

	if (announcement.getText() != "") {
		announcement.Draw(window);
	}

}

void Room::MakeAnnouncement(const std::string& message, unsigned int duration) {
	std::string& text = (std::string&)announcement.getText();
	std::thread{ make_anouncement, message, duration, &text }.detach();
}

void Room::ServerUpdate(const std::string& message) {
	Json recieve = Util::JsonParse((std::string&)message);

	if (recieve.GetValue("action") == "announce") {
		MakeAnnouncement(recieve.GetValue("message"), std::stoi(recieve.GetValue("duration")));
	}
	else {
		message_queue.push_back(recieve);
	}
}

void* Room::GetState() {
	return state;
}
