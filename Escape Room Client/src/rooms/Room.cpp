#pragma once

#include "rooms/Room.hpp"
#include <ctime>

struct reserved_state {
	bool playing; //Is the game being played
	bool victory; //Has the game been won
	long long end_time;
};

void make_anouncement(const std::string& message, unsigned int duration, std::string* output) {
	*output = message;
	std::this_thread::sleep_for(std::chrono::seconds(duration));
	*output = "";
}

Room::Room(const std::string& data, unsigned int byte_count) : byte_count(byte_count), state(nullptr),
announcement("", "width: 94%;height: 6%;left:3%;bottom: 85%;text-align:center;colour:#FFFFFF00;text-size:auto large;"),
timer("--:--","width: 10%;height: 5%;left: 85;bottom: 85%;text-align:center;colour:#FFFFFFFF;text-size:auto large;") {
	state = malloc(byte_count);

	if (state) {
		memcpy(state, data.data(), byte_count);
	}
}

void Room::LocalUpdate(Environment& env) {
	reserved_state* data = (reserved_state*)state;
	
	if (announcement.getText() != "") {
		announcement.Update(env);
		announcement.Draw(*env.window);
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
	timer.Draw(*env.window);
}

void Room::MakeAnnouncement(const std::string& message, unsigned int duration) {
	std::string& text = (std::string&)announcement.getText();
	std::thread{ make_anouncement, message, duration, &text }.detach();
}

void Room::ServerUpdate(const std::string& message) {
	Json recieve = Util::JsonParse((std::string&)message);

	if (recieve.GetValue("action") == "room_update") {

		memcpy(state, recieve.GetValue("state").data(), byte_count);
	}
	else if (recieve.GetValue("action") == "player_join") {
		//players.push_back(recieve.GetValue("username"));
		players.emplace_back(recieve.GetValue("username"));

		MakeAnnouncement(recieve.GetValue("username") + " joined.", 5);
		
	}
	else if (recieve.GetValue("action") == "announce") {
		//std::thread{ make_anouncement, "", 5, announcement }.detach();
	}
}

void* Room::GetState() {
	return state;
}