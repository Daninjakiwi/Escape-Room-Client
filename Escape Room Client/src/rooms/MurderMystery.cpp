#include "rooms/MurderMystery.hpp"
#include "core/Network.hpp"


struct murder_mystery_data {
	bool playing; //Is the game being played
	bool victory; //Has the game been won
	long long end_time;
	bool old_key_found;
	bool cabinet_open;
	unsigned int door_combination;
};

void start_click(Button* btn, Environment& env) {
	Json send;

	send.AddPair("action", "start");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);

	env.server->Send(send);

	/*
	Json send;
	send.AddPair("action", "update");
	send.AddPair("message", "cabinet_opened");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);

	env.server->Send(send);
	*/
}

MurderMystery::MurderMystery(const std::string& data) : Room(data, 16),
mat("resources/images/pbr/gold"),
btn_start("Start game", "width: 30%;height: 5%;left: 35%;bottom: 70%;text-size:auto 80%;text-align:center;colour:#FFFFFF;hover colour:#CCCCCC;click colour:#777777;"),
floor(20,20){
	btn_start.SetOnClick(start_click);
	floor.SetMaterial(&mat);
}

void MurderMystery::LocalUpdate(Environment& env) {
	//Room::LocalUpdate(env);
	env.window->lockCursor();

	for (auto it = players.begin(); it < players.end(); it++) {
		it->Update(env);
	}


	username = env.username;

	murder_mystery_data* data = (murder_mystery_data*)state;

	if (data->playing) {

	}
	else {
		if (players.size() > 0 && players[0].GetName() == username) {
			btn_start.Update(env);
		}
	}
	
	floor.Update(env);
}

void MurderMystery::Draw(volt::Window& window) {
	murder_mystery_data* data = (murder_mystery_data*)state;

	if (data->playing) {

	}
	else {
		if (players.size() > 0 && players[0].GetName() == username) {
			//btn_start.Draw(window);
		}
	}

	floor.Draw(window);

}