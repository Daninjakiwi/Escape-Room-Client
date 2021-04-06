#include "rooms/MurderMystery.hpp"
#include "core/Network.hpp"
#include "objects/Ground.hpp"
#include "objects/Wall.hpp"

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
btn_start("Start game", "width: 30%;height: 5%;left: 35%;bottom: 70%;text-size:auto 80%;text-align:center;colour:#FFFFFF;hover colour:#CCCCCC;click colour:#777777;")
{
	//LOAD MATERIALS
	materials.emplace("gold", new volt::PbrMaterial("resources/images/pbr/gold"));
	materials.emplace("brick", new volt::PbrMaterial("resources/images/pbr/brick"));
	materials.emplace("grass", new volt::PbrMaterial("resources/images/pbr/grass"));

	//LOAD MESHES



	meshes.emplace("cube", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE)));
	meshes.emplace("wall", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE, { 10.0f,2.0f })));

	//LOAD OBJECTS

	Ground* ground = new Ground({ 50.0f,50.0f });

	ground->SetMaterial(materials["grass"]);
	ground->SetMesh(meshes["cube"]);

	objects.emplace("ground", ground);

	for (int i = 0; i < 4; i++) {
		volt::Vec3 size;
		volt::Vec3 pos;

		if (i % 2 == 0) {
			size = { 1.0f,10.0f,50.0f };
			if (i == 2) {
				pos = { 50.0f,0.0f,0.0f };
			}
		}
		else {
			size = { 50.0f,10.0f,1.0f };

			if (i == 3) {
				pos = { 0.0f,0.0f,-50.0f };
			}
		}
		Wall* wall = new Wall(size, pos);

		wall->SetMaterial(materials["brick"]);
		wall->SetMesh(meshes["wall"]);

		objects.emplace("wall" + std::to_string(i), wall);

	
	}

	Wall* wall = new Wall({ 1.0f, 10.0f,50.0f }, {-20.0f,0.0f,0.0f});

	wall->SetMaterial(materials["brick"]);
	wall->SetMesh(meshes["wall"]);

	objects.emplace("wall4", wall);

	

	

	

	btn_start.SetOnClick(start_click);
}

void MurderMystery::LocalUpdate(Environment& env) {
	murder_mystery_data* data = (murder_mystery_data*)state;

	Room::LocalUpdate(env);

	if (data->playing) {
		env.window->lockCursor();

		
	}

	for (auto it = players.begin(); it < players.end(); it++) {
		it->Update(env);
	}


	username = env.username;



	if (data->playing) {

	}
	else {
		if (players.size() > 0 && players[0].GetName() == username) {
			btn_start.Update(env);
		}
	}

	for (auto [name, obj] : objects) {
		obj->Update(env);
	}

	
}

void MurderMystery::Draw(volt::Window& window) {
	murder_mystery_data* data = (murder_mystery_data*)state;

	if (data->playing) {

	}
	else {
		if (players.size() > 0 && players[0].GetName() == username) {
			btn_start.Draw(window);
		}
	}

	for (auto [name, obj] : objects) {
		obj->Draw(window);
	}

}