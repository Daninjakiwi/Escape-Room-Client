#include "rooms/MurderMystery.hpp"
#include "core/Network.hpp"
#include "objects/Ground.hpp"
#include "objects/Wall.hpp"
#include "meshes/PlayerMesh.hpp"
#include "meshes/LoadMesh.hpp"
#include "objects/ChessBoard.hpp"
#include "objects/CardboardBox.hpp"
#include "objects/Door.hpp"
#include "objects/Desk.hpp"
#include "objects/Drawer.hpp"
#include "objects/Cabinet.hpp"
#include "objects/MurderMystery/CabinetDoor.hpp"
#include "objects/MurderMystery/Safe.hpp"
#include "objects/MurderMystery/RugCorner.hpp"
#include "objects/MurderMystery/SmartShoes.hpp"
#include "objects/Note.hpp"
#include "objects/MurderMystery/Vest.hpp"
#include "objects/MurderMystery/Chest.hpp"
#include "objects/MurderMystery/Drill.hpp"
#include "core/Scene.hpp"
#include <ctime>


void start_click(Button* btn, Environment& env) {
	Json send;

	send.AddPair("action", "start");
	send.AddPair("token", env.token);
	send.AddPair("code", env.code);

	env.server->Send(send);
}

void copy_click(Button* btn, Environment& env) {
	HGLOBAL data = GlobalAlloc(GMEM_FIXED, 32);
	if (data) {
		memcpy(data, env.code.c_str(), env.code.length() + 1);

		if (OpenClipboard(nullptr)) {
			EmptyClipboard();
			SetClipboardData(CF_TEXT, data);
			CloseClipboard();
		}

	}

	GlobalFree(data);
}

void BtnQuitClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Home");
	env.window->setBackgroundColour({ 0.1f,0.1f,0.1f,1.0f });
}

MurderMystery::MurderMystery(const std::string& data, Environment& env) : Room(data, 64, 1, 4),
btn_start("Start", "width: 18%;height: 8%;left: 79%;bottom: 7%;text-size:auto 80%;text-align:center;colour:#00000000;text-colour:#FFFFFF;hover colour:#1286A8;"),
btn_copy("Copy", "width: 8%;height: 4%;left: 67%;bottom: 88%;text-size:auto 80%;colour:#00000000;text-colour:#FFFFFF;hover colour:#1286A8;text-align:center;"),
btn_quit("Exit", "width: 18%;height: 8%;left: 41%;bottom: 15%;text-size:auto 80%;text-align:center;colour:#00000000;text-colour:#FFFFFF;hover colour:#1286A8;"),
lbl_scenario("You have woken up and heard shouting in your neighbours house. When you and your other neighbours arrive there, you find the owner on the floor wounded. The door slams shut behind you all and you hear the sound of a key turning. You must find a way to escape the room quickly to ensure the safety of the owner.", "width: 73%;left: 3%;bottom: 80%;text-size: 0.06h;text-colour:#FFFFFF;"),
lbl_players_list("Players", "width: 20%;left: 79%;bottom:76%;max-words: 2;text-size: 0.05h;text-colour:#FFFFFF;"),
lbl_title("Crime Scene", "width: 30%;height: 10%;left: 2%;bottom: 85%;text-size:auto 80%;text-align:left;colour:#00000000;text-colour:#FFFFFF;"),
lbl_waiting("Waiting for Players", "width: 20%;height:5%;left: 78%;bottom: 85%;text-size:auto 90%;text-align:center;colour:#00000000;text-colour:#FFFFFF;"),
lbl_code("Code: " + env.code, "width: 25%;height: 8%;left:42%;bottom: 86%;text-size:auto 60%;text-align:right;colour:#00000000;text-colour:#FFFFFF;"),
lbl_victory("Victory!", "width: 20%;height: 10%;left: 40%;bottom: 45%;text-size:auto 70%;text-align:center;colour:#00000000;text-colour:#FFFFFF;"),
lbl_time_taken("", "width: 16%;height: 10%;left: 42%;bottom: 32%;text-size:auto 70%;text-align:center;colour:#00000000;text-colour:#FFFFFF;"),
main_panel("width: 74%;height: 80%;bottom: 5%;left: 2%;colour:#303030FF;"),
side_panel("width: 20%;height: 90%;left: 78%;bottom: 5%;colour:#303030FF;")
{
	btn_quit.SetOnClick(BtnQuitClick);

	auto start = std::chrono::high_resolution_clock::now();
	username = env.username;

	Label loading_text("", "width: 50%;height: 8%;left: 45%;bottom: 10%;text-colour:#FFFFFF;text-size:auto 100%;text-align:right;colour:#00000000;");

	volt::Vec3 light_colour = { 30.0f,30.0f,4.0f };

	volt::Light lights[6] = {
	{{23.7f,12.6f,-25.7f},light_colour},
	{{26.3f,12.6f,-25.7},light_colour},
	{{25.1f, 12.6f, -26.5f},light_colour },
	{{23.7f, 12.6f, -24.2f}, light_colour},
	{{26.3f,12.6f, -24.2f},light_colour},
	{{25.0f,12.6f, -23.4f},light_colour}
	};

	for (int i = 0; i < 6; i++) {
		env.window->setLight(i, lights[i]);
	}

	//LOAD MATERIALS
	materials.emplace("gold", new volt::PbrMaterial("resources/textures/pbr/metal/gold"));
	materials.emplace("iron", new volt::PbrMaterial("resources/textures/pbr/metal/iron"));
	materials.emplace("red_carpet", new volt::PbrMaterial("resources/textures/pbr/red_carpet"));
	materials.emplace("wallpaper", new volt::PbrMaterial("resources/textures/pbr/wallpaper/floral"));
	materials.emplace("plaster", new volt::PbrMaterial("resources/textures/pbr/plaster"));
	materials.emplace("walnut", new volt::PbrMaterial("resources/textures/pbr/wood/walnut"));
	materials.emplace("ash", new volt::PbrMaterial("resources/textures/pbr/wood/ash"));
	materials.emplace("rug", new volt::PbrMaterial("resources/textures/pbr/rug"));
	materials.emplace("bench", new volt::PbrMaterial("resources/textures/pbr/bench"));
	materials.emplace("vest", new volt::PbrMaterial("resources/textures/pbr/vest"));
	materials.emplace("hoodie", new volt::PbrMaterial("resources/textures/pbr/hoodie"));
	materials.emplace("chandelier", new volt::PbrMaterial("resources/textures/pbr/chandelier"));
	materials.emplace("trainers", new volt::PbrMaterial("resources/textures/pbr/trainers"));
	materials.emplace("boots", new volt::PbrMaterial("resources/textures/pbr/boots"));
	materials.emplace("suede_shoe", new volt::PbrMaterial("resources/textures/pbr/suede_shoe"));
	materials.emplace("yellow", new volt::ColourMaterial({ 1.0f,0.9f,0.0f,1.0f }));
	materials.emplace("note", new volt::PbrMaterial("resources/textures/pbr/paper_note"));
	materials.emplace("drill", new volt::PbrMaterial("resources/textures/pbr/drill"));
	materials.emplace("chest", new volt::PbrMaterial("resources/textures/pbr/chest"));
	materials.emplace("book_group", new volt::PbrMaterial("resources/textures/pbr/book_group"));
	materials.emplace("chair", new volt::PbrMaterial("resources/textures/pbr/chair"));
	materials.emplace("book", new volt::PbrMaterial("resources/textures/pbr/book"));
	materials.emplace("umbrella", new volt::PbrMaterial("resources/textures/pbr/umbrella"));
	materials.emplace("stick", new volt::PbrMaterial("resources/textures/pbr/stick"));
	materials.emplace("painting", new volt::PbrMaterial("resources/textures/pbr/painting"));
	materials.emplace("painting2", new volt::PbrMaterial("resources/textures/pbr/painting2"));
	materials.emplace("player", new volt::ColourMaterial({ 0.0f,0.0f,1.0f,1.0f }));

	loading_text.setText("Loading Meshes");
	loading_text.Update(env);
	loading_text.Draw(*env.window);
	env.window->update();

	//LOAD MESHES
	meshes.emplace("player", new volt::Mesh(Meshes::PlayerMesh()));
	meshes.emplace("cube", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE)));
	meshes.emplace("wall", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE, { 5.0f,2.0f })));
	meshes.emplace("wall_short", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE, { 1.0f,2.0f })));
	meshes.emplace("wall_long", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE, { 1.14f,0.4f })));
	meshes.emplace("wall_internal", new volt::Mesh(volt::Mesh::createPrimative(volt::PrimativeTypes::CUBE, { 1.71f,2.0f })));
	meshes.emplace("bookshelf", new volt::Mesh(Meshes::Load("resources/meshes/bookshelf.obj")));
	meshes.emplace("floor", new volt::Mesh(Meshes::Load("resources/meshes/floor.obj")));
	meshes.emplace("rug", new volt::Mesh(Meshes::Load("resources/meshes/rug.obj")));
	meshes.emplace("bench", new volt::Mesh(Meshes::Load("resources/meshes/bench.obj")));
	meshes.emplace("hoodie", new volt::Mesh(Meshes::Load("resources/meshes/hoodie.obj")));
	meshes.emplace("vest", new volt::Mesh(Meshes::Load("resources/meshes/vest.obj")));
	meshes.emplace("chandelier", new volt::Mesh(Meshes::Load("resources/meshes/chandelier.obj")));
	meshes.emplace("basket", new volt::Mesh(Meshes::Load("resources/meshes/bin.obj")));
	meshes.emplace("boots", new volt::Mesh(Meshes::Load("resources/meshes/boots.obj")));
	meshes.emplace("trainers", new volt::Mesh(Meshes::Load("resources/meshes/trainers.obj")));
	meshes.emplace("suede_shoe", new volt::Mesh(Meshes::Load("resources/meshes/suede_shoe.obj")));
	meshes.emplace("drill", new volt::Mesh(Meshes::Load("resources/meshes/drill.obj")));
	meshes.emplace("chest", new volt::Mesh(Meshes::Load("resources/meshes/chest.obj")));
	meshes.emplace("chair", new volt::Mesh(Meshes::Load("resources/meshes/chair.obj")));
	meshes.emplace("book", new volt::Mesh(Meshes::Load("resources/meshes/book.obj")));
	meshes.emplace("umbrella", new volt::Mesh(Meshes::Load("resources/meshes/umbrella.obj")));
	meshes.emplace("stick", new volt::Mesh(Meshes::Load("resources/meshes/stick.obj")));
	meshes.emplace("painting", new volt::Mesh(Meshes::Load("resources/meshes/painting.obj")));
	meshes.emplace("frame", new volt::Mesh(Meshes::Load("resources/meshes/frame.obj")));

	std::vector<volt::Mesh> chess_pieces = Meshes::LoadSeperate("resources/meshes/chess_pieces.obj");

	meshes.emplace("pawn", new volt::Mesh(chess_pieces[0]));
	meshes.emplace("rook", new volt::Mesh(chess_pieces[1]));
	meshes.emplace("knight", new volt::Mesh(chess_pieces[2]));
	meshes.emplace("bishop", new volt::Mesh(chess_pieces[3]));
	meshes.emplace("queen", new volt::Mesh(chess_pieces[4]));
	meshes.emplace("king", new volt::Mesh(chess_pieces[5]));



	std::vector<volt::Mesh> book_meshes = Meshes::LoadSeperate("resources/meshes/book_group.obj");

	for (int i = 0; i < 4; i++) {
		meshes.emplace("book_group" + std::to_string(i), new volt::Mesh(book_meshes[i]));
	}


	objects.emplace("test", new GameObject());
	objects["test"]->SetMesh(meshes["test"]);
	objects["test"]->SetMaterial(materials["gold"]);
	objects["test"]->_transform.scale *= 0.05f;


	objects.emplace("painting", new GameObject());
	objects["painting"]->SetMesh(meshes["painting"]);
	objects["painting"]->SetMaterial(materials["painting"]);
	objects["painting"]->_transform.scale *= 5.0f;
	objects["painting"]->_transform.position = { 20.0f,-1.8f,-32.0f };

	objects.emplace("frame", new GameObject());
	objects["frame"]->SetMesh(meshes["frame"]);
	objects["frame"]->SetMaterial(materials["gold"]);
	objects["frame"]->_transform.scale *= 0.1f;
	objects["frame"]->_transform.position = { 50.0f,8.0f,-36.0f };
	objects["frame"]->_transform.rotation.y = -90.0f;

	objects.emplace("painting2", new GameObject());
	objects["painting2"]->SetMesh(meshes["cube"]);
	objects["painting2"]->SetMaterial(materials["painting2"]);
	objects["painting2"]->_transform.scale = { 0.2f,4.5f,10.1f };
	objects["painting2"]->_transform.position = { 49.9f,8.8f,-25.1f };

	objects.emplace("chair", new GameObject());
	objects["chair"]->SetMesh(meshes["chair"]);
	objects["chair"]->SetMaterial(materials["chair"]);
	objects["chair"]->_transform.scale *= 0.04f;
	objects["chair"]->_transform.position = { 37.0f,1.0f,-33.0f };
	objects["chair"]->_transform.rotation.y = 60.0f;

	objects.emplace("book", new GameObject());
	objects["book"]->SetMesh(meshes["book"]);
	objects["book"]->SetMaterial(materials["book"]);
	objects["book"]->_transform.scale *= 6.0f;
	objects["book"]->_transform.position = { 15.0f,4.6f,-49.0f };
	objects["book"]->_transform.rotation = { 90.0f,0.0f,90.0f };

	objects.emplace("umbrella", new GameObject());
	objects["umbrella"]->SetMesh(meshes["umbrella"]);
	objects["umbrella"]->SetMaterial(materials["umbrella"]);
	objects["umbrella"]->_transform.scale *= 0.17f;
	objects["umbrella"]->_transform.position = { 3.0f,0.7f,-4.2f };
	objects["umbrella"]->_transform.rotation.x = 20.0f;

	objects.emplace("stick", new GameObject());
	objects["stick"]->SetMesh(meshes["stick"]);
	objects["stick"]->SetMaterial(materials["stick"]);
	objects["stick"]->_transform.scale *= 6.5f;
	objects["stick"]->_transform.position = {3.7f, 1.2f, -3.3f};
	objects["stick"]->_transform.rotation = { -25.0f,0.0f,20.0f };

	objects.emplace("chest_interact", new Chest());

	objects.emplace("book_group0", new GameObject());
	objects["book_group0"]->SetMesh(meshes["book_group0"]);
	objects["book_group0"]->SetMaterial(materials["book_group"]);
	objects["book_group0"]->_transform.scale = { 9.2f,10.0f,10.0f };
	objects["book_group0"]->_transform.position = { 14.8f,-4.0f,-48.5f };
	objects["book_group0"]->_transform.rotation.x = -90.0f;
	objects["book_group0"]->_hitbox = new Hitbox({12.0f,1.0f,-48.0f}, {21.0f,3.0f,2.0f});

	objects.emplace("book_group1", new GameObject());
	objects["book_group1"]->SetMesh(meshes["book_group0"]);
	objects["book_group1"]->SetMaterial(materials["book_group"]);
	objects["book_group1"]->_transform.scale = { 9.2f,10.0f,10.0f };
	objects["book_group1"]->_transform.position = { 22.0f,-0.8f,-48.5f };
	objects["book_group1"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group2", new GameObject());
	objects["book_group2"]->SetMesh(meshes["book_group0"]);
	objects["book_group2"]->SetMaterial(materials["book_group"]);
	objects["book_group2"]->_transform.scale = { 9.2f,10.0f,10.0f };
	objects["book_group2"]->_transform.position = { 29.0f,-9.0f,-48.5f };
	objects["book_group2"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group3", new GameObject());
	objects["book_group3"]->SetMesh(meshes["book_group1"]);
	objects["book_group3"]->SetMaterial(materials["book_group"]);
	objects["book_group3"]->_transform.scale = {6.0f,12.0f,8.0f };
	objects["book_group3"]->_transform.position = { 23.0f,-6.6f,-48.5f };
	objects["book_group3"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group4", new GameObject());
	objects["book_group4"]->SetMesh(meshes["book_group1"]);
	objects["book_group4"]->SetMaterial(materials["book_group"]);
	objects["book_group4"]->_transform.scale = { 6.0f,12.0f,8.0f };
	objects["book_group4"]->_transform.position = { 16.0f,-8.0f,-48.5f };
	objects["book_group4"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group5", new GameObject());
	objects["book_group5"]->SetMesh(meshes["book_group1"]);
	objects["book_group5"]->SetMaterial(materials["book_group"]);
	objects["book_group5"]->_transform.scale = { 6.0f,12.0f,8.0f };
	objects["book_group5"]->_transform.position = { 30.0f,-1.6f,-48.5f };
	objects["book_group5"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group6", new GameObject());
	objects["book_group6"]->SetMesh(meshes["book_group2"]);
	objects["book_group6"]->SetMaterial(materials["book_group"]);
	objects["book_group6"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group6"]->_transform.position = { 30.0f,0.8f,-48.5f };
	objects["book_group6"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group7", new GameObject());
	objects["book_group7"]->SetMesh(meshes["book_group2"]);
	objects["book_group7"]->SetMaterial(materials["book_group"]);
	objects["book_group7"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group7"]->_transform.position = { 16.0f,5.6f,-48.5f };
	objects["book_group7"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group8", new GameObject());
	objects["book_group8"]->SetMesh(meshes["book_group2"]);
	objects["book_group8"]->SetMaterial(materials["book_group"]);
	objects["book_group8"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group8"]->_transform.position = { 23.0f,0.7f,-48.5f };
	objects["book_group8"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group9", new GameObject());
	objects["book_group9"]->SetMesh(meshes["book_group3"]);
	objects["book_group9"]->SetMaterial(materials["book_group"]);
	objects["book_group9"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group9"]->_transform.position = { 23.0f,-0.7f,-48.5f };
	objects["book_group9"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group10", new GameObject());
	objects["book_group10"]->SetMesh(meshes["book_group3"]);
	objects["book_group10"]->SetMaterial(materials["book_group"]);
	objects["book_group10"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group10"]->_transform.position = { 30.0f,1.0f,-48.5f };
	objects["book_group10"]->_transform.rotation.x = -90.0f;

	objects.emplace("book_group11", new GameObject());
	objects["book_group11"]->SetMesh(meshes["book_group3"]);
	objects["book_group11"]->SetMaterial(materials["book_group"]);
	objects["book_group11"]->_transform.scale = { 6.0f,8.0f,8.0f };
	objects["book_group11"]->_transform.position = { 16.0f,0.9f,-48.5f };
	objects["book_group11"]->_transform.rotation.x = -90.0f;

	objects.emplace("cabinet_middle", new GameObject());
	objects["cabinet_middle"]->SetMesh(meshes["cube"]);
	objects["cabinet_middle"]->SetMaterial(materials["walnut"]);
	objects["cabinet_middle"]->_transform.scale = { 5.0f,5.8f,0.2f };
	objects["cabinet_middle"]->_transform.position = { 1.55f,1.0f,-28.0f };

	objects.emplace("drill", new GameObject());
	objects["drill"]->SetMesh(meshes["drill"]);
	objects["drill"]->SetMaterial(materials["drill"]);
	objects["drill"]->_transform.scale *= 8.0f;
	objects["drill"]->_transform.position = { 20.0f,-2.3f,-34.0f };
	objects["drill"]->_transform.rotation.x = -90.0f;

	objects.emplace("drill_interact", new Drill());

	objects.emplace("chest", new GameObject());
	objects["chest"]->SetMesh(meshes["chest"]);
	objects["chest"]->SetMaterial(materials["chest"]);
	objects["chest"]->_transform.scale *= 0.12f;
	objects["chest"]->_transform.rotation.y = 60.0f;
	objects["chest"]->_transform.position = { 39.4f,5.6f,-28.0f };

	objects.emplace("smart_shoes", new SmartShoes());

	objects.emplace("boots", new GameObject());
	objects["boots"]->SetMesh(meshes["boots"]);
	objects["boots"]->SetMaterial(materials["boots"]);
	objects["boots"]->_transform.scale *= 7.0f;
	objects["boots"]->_transform.position = { 47.0f, 5.2f,-5.0f };
	objects["boots"]->_transform.rotation.y = -120.0f;

	objects.emplace("trainers", new GameObject());
	objects["trainers"]->SetMesh(meshes["trainers"]);
	objects["trainers"]->SetMaterial(materials["trainers"]);
	objects["trainers"]->_transform.scale *= 0.25f;
	objects["trainers"]->_transform.position = { 47.0f, 5.0f,-8.6f };
	objects["trainers"]->_transform.rotation.y = -90.0f;

	objects.emplace("suede_shoe", new GameObject());
	objects["suede_shoe"]->SetMesh(meshes["suede_shoe"]);
	objects["suede_shoe"]->SetMaterial(materials["suede_shoe"]);
	objects["suede_shoe"]->_transform.scale *= 0.007f;
	objects["suede_shoe"]->_transform.position = { 47.0f, 5.6f, -11.0f };
	objects["suede_shoe"]->_transform.rotation = { 0.0,90.0f,0.0f };

	objects.emplace("suede_shoe2", new GameObject());
	objects["suede_shoe2"]->SetMesh(meshes["suede_shoe"]);
	objects["suede_shoe2"]->SetMaterial(materials["suede_shoe"]);
	objects["suede_shoe2"]->_transform.scale *= 0.007f;
	objects["suede_shoe2"]->_transform.scale.z *= -1.0f;
	objects["suede_shoe2"]->_transform.position = { 47.0f, 5.6f, -12.0f };
	objects["suede_shoe2"]->_transform.rotation.y = -90.0f;

	objects.emplace("chandelier", new GameObject());
	objects["chandelier"]->SetMesh(meshes["chandelier"]);
	objects["chandelier"]->SetMaterial(materials["chandelier"]);
	objects["chandelier"]->_transform.scale *= 4.0f;
	objects["chandelier"]->_transform.position = { 25.0f,15.0f,-25.0f };

	objects.emplace("safe", new Safe());
	objects["safe"]->_transform.scale *= 0.0175f;
	objects["safe"]->_transform.rotation.x = -90.0f;
	objects["safe"]->_transform.position = { 20.0f,-1.2f,-32.9f };


	auto coat_hook_meshes = Meshes::LoadSeperate("resources/meshes/coat_hook.obj");


	meshes.emplace("coat_hook", new volt::Mesh(coat_hook_meshes[0]));
	meshes.emplace("coat_hook_plate", new volt::Mesh(coat_hook_meshes[3]));


	objects.emplace("bench", new GameObject());
	objects["bench"]->SetMesh(meshes["bench"]);
	objects["bench"]->SetMaterial(materials["bench"]);
	objects["bench"]->_transform.scale *= 0.1f;
	objects["bench"]->_transform.rotation.y = 90.0f;
	objects["bench"]->_transform.position = { 47.0f,1.0f,-8.0f };

	objects.emplace("coat_hook_plate", new GameObject());
	objects["coat_hook_plate"]->SetMesh(meshes["coat_hook_plate"]);
	objects["coat_hook_plate"]->SetMaterial(materials["ash"]);
	objects["coat_hook_plate"]->_transform.position = { 51.0f, 11.0f,-1.0f };
	objects["coat_hook_plate"]->_transform.rotation.y = 180.0f;
	objects["coat_hook_plate"]->_transform.scale *= 0.7f;

	for (int i = 0; i < 3; i++) {
		GameObject* hook = new GameObject();
		hook->SetMesh(meshes["coat_hook"]);
		hook->SetMaterial(materials["gold"]);
		hook->_transform.position = { 48.0f - (i * 2.5f),11.3f,-1.0f };
		hook->_transform.rotation.y = 180.0f;
		hook->_transform.scale *= 0.4f;
		objects.emplace("coat_hook" + std::to_string(i), hook);
	}

	objects.emplace("hoodie", new GameObject());
	objects["hoodie"]->SetMesh(meshes["hoodie"]);
	objects["hoodie"]->SetMaterial(materials["hoodie"]);
	objects["hoodie"]->_transform.position = { 38.2f, 1.35f, -2.0f };
	objects["hoodie"]->_transform.scale *= 0.055f;

	objects.emplace("vest", new GameObject());
	objects["vest"]->SetMesh(meshes["vest"]);
	objects["vest"]->SetMaterial(materials["vest"]);
	objects["vest"]->_transform.position = { 40.7f, 10.35f, -1.0f };
	objects["vest"]->_transform.scale *= 1.5f;

	objects.emplace("vest_interact", new Vest());

	objects.emplace("basket", new GameObject());
	objects["basket"]->SetMesh(meshes["basket"]);
	objects["basket"]->SetMaterial(materials["iron"]);
	objects["basket"]->_transform.scale = { 0.07f,0.08f,0.07f };
	objects["basket"]->_transform.position = { 3.0f,1.0f,-3.8f };



	//LOAD OBJECTS

	Door* door = new Door();

	objects.emplace("door", door);
	objects["door"]->_transform.position = { 0.5f,1.0f,-11.0f };
	objects["door"]->_transform.rotation = { 0.0f,90.0f,0.0f };
	objects["door"]->_transform.scale = { 40.0f,26.0f,40.0f };
	objects["door"]->_hitbox = new Hitbox({ 0.0f,0.0f,-7.0f }, { 1.0f,12.0f,8.0f });

	Ground* ground = new Ground({ 1.0f,1.0f });

	ground->SetMaterial(materials["red_carpet"]);
	ground->SetMesh(meshes["floor"]);
	ground->_hitbox->size = { 50.0f,1.0f,50.0f };

	objects.emplace("ground", ground);

	ground = new Ground({ 50.0f,50.0f });
	ground->SetMaterial(materials["plaster"]);
	ground->SetMesh(meshes["floor"]);
	ground->_transform.position.y += 15.0f;
	//ground->_hitbox->position.y += 15.0f;

	objects.emplace("ground2", ground);


	for (int i = 1; i < 4; i++) {
		volt::Vec3 size;
		volt::Vec3 pos;

		if (i % 2 == 0) {
			size = { 1.0f,15.0f,50.0f };
			if (i == 2) {
				pos = { 50.0f,0.0f,0.0f };
			}
		}
		else {
			size = { 50.0f,15.0f,1.0f };

			if (i == 3) {
				pos = { 0.0f,0.0f,-50.0f };
			}
		}

		Wall* wall = new Wall(size, pos);

		wall->SetMaterial(materials["wallpaper"]);
		wall->SetMesh(meshes["wall"]);

		objects.emplace("wall" + std::to_string(i), wall);



	}

	Wall* wall = new Wall({ 1.0f,15.0f,7.0f }, { 0.0f,0.0f,0.0f });

	wall->SetMaterial(materials["wallpaper"]);
	wall->SetMesh(meshes["wall_short"]);

	objects.emplace("wall4", wall);

	wall = new Wall({ 1.0f,15.0f,35.0f }, { 0.0f,0.0f,-15.0f });

	wall->SetMaterial(materials["wallpaper"]);
	wall->SetMesh(meshes["wall"]);

	objects.emplace("wall5", wall);

	wall = new Wall({ 1.0f, 2.6f, 8.0f }, { 0.0f,12.4f, -7.0f });
	wall->SetMaterial(materials["wallpaper"]);
	wall->SetMesh(meshes["wall_long"]);

	objects.emplace("wall6", wall);

	wall = new Wall({ 12.0f, 15.0f, 0.8f }, { 38.0f, 0.0f, -15.0f });
	wall->SetMaterial(materials["wallpaper"]);
	wall->SetMesh(meshes["wall_internal"]);

	objects.emplace("wall7", wall);

	objects.emplace("chess", new ChessBoard());
	objects["chess"]->_transform.position = { 47.0f,6.2f,-33.6f };
	objects["chess"]->_transform.scale = { 3.0f,2.5f,3.0f };
	objects["chess"]->_transform.rotation.y = 65.0f;


	Desk* desk = new Desk();

	objects.emplace("desk", desk);
	objects["desk"]->_transform.position = { 45.0f,1.0f,-30.0f };
	objects["desk"]->_transform.rotation.y = -90.0f;
	objects["desk"]->_transform.scale = { 9.0f, 6.5f, 9.0f };

	objects.emplace("drawer0", new Drawer(0));
	objects["drawer0"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 4.5f, desk->_transform.position.z + 3.5f }, { 1.0f,0.4f,6.0f });

	objects.emplace("drawer1", new Drawer(1));
	objects["drawer1"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 4.5f, desk->_transform.position.z + 8.0f }, { 1.0f,0.4f,4.0f });

	objects.emplace("drawer2", new Drawer(2));
	objects["drawer2"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 3.0f, desk->_transform.position.z + 8.0f }, { 1.0f,0.8f,4.0f });

	objects.emplace("drawer3", new Drawer(3));
	objects["drawer3"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 1.9f, desk->_transform.position.z + 8.0f }, { 1.0f,0.8f,4.0f });

	objects.emplace("drawer4", new Drawer(4));
	objects["drawer4"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 0.7f, desk->_transform.position.z + 8.0f }, { 1.0f,0.8f,4.0f });

	objects.emplace("drawer5", new Drawer(5));
	objects["drawer5"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 4.5f, desk->_transform.position.z - 3.0f }, { 1.0f,0.4f,4.0f });

	objects.emplace("drawer6", new Drawer(6));
	objects["drawer6"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 3.0f, desk->_transform.position.z - 3.0f }, { 1.0f,0.8f,4.0f });

	objects.emplace("drawer7", new Drawer(7));
	objects["drawer7"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 1.9f, desk->_transform.position.z - 3.0f }, { 1.0f,0.8f,4.0f });

	objects.emplace("drawer8", new Drawer(8));
	objects["drawer8"]->_hitbox = new Hitbox({ desk->_transform.position.x - 4.5f, desk->_transform.position.y + 0.7f, desk->_transform.position.z - 3.0f }, { 1.0f,0.8f,4.0f });


	Cabinet* cabinet = new Cabinet();
	objects.emplace("cabinet", cabinet);
	objects["cabinet"]->_transform.rotation.y = 90.0f;
	objects["cabinet"]->_transform.position = { 5.2f,-2.0f,-25.0f };
	objects["cabinet"]->_transform.scale = { 0.3f,0.22f,0.3f };

	objects.emplace("cabinet_door0", new CabinetDoor(0));
	objects["cabinet_door0"]->_hitbox = new Hitbox({ cabinet->_transform.position.x + 0.5f, cabinet->_transform.position.y + 3.5f, cabinet->_transform.position.z + 3.0f }, { 1.0f,5.0f,6.0f });

	objects.emplace("cabinet_door1", new CabinetDoor(1));
	objects["cabinet_door1"]->_hitbox = new Hitbox({ cabinet->_transform.position.x + 0.5f, cabinet->_transform.position.y + 3.5f, cabinet->_transform.position.z - 4.0f }, { 1.0f,5.0f,5.0f });

	for (int i = 0; i < 3; i++) {
		objects.emplace("bookshelf" + std::to_string(i), new GameObject());
		objects["bookshelf" + std::to_string(i)]->SetMesh(meshes["bookshelf"]);
		objects["bookshelf" + std::to_string(i)]->SetMaterial(materials["walnut"]);
		objects["bookshelf" + std::to_string(i)]->_transform.position = { 15.0f + (7.0f * i),1.0f,-48.5f };
		objects["bookshelf" + std::to_string(i)]->_transform.scale *= 5.0f;
	}

	objects.emplace("box0", new CardboardBox(0, 1));
	objects["box0"]->_transform.position = { 4.0f, 1.0f, -38.0f };
	objects["box0"]->_transform.scale *= 1.5f;
	objects["box0"]->_transform.rotation.y = -70.0f;

	objects.emplace("box1", new CardboardBox(2, 0));
	objects["box1"]->_transform.position = { 4.0f, 1.0f, -47.0f };
	objects["box1"]->_transform.scale *= 0.9f;
	objects["box1"]->_transform.rotation.y = 65.0f;

	objects.emplace("box2", new CardboardBox(2, 2));
	objects["box2"]->_transform.position = { 3.5f, 1.0f, -42.0f };
	objects["box2"]->_transform.scale *= 0.5f;
	objects["box2"]->_transform.rotation.y = 90.0f;

	objects.emplace("box3", new CardboardBox(0, 0));
	objects["box3"]->_transform.position = { 4.0f, 4.4f, -46.5f };
	objects["box3"]->_transform.scale *= 1.2f;
	objects["box3"]->_transform.rotation.y = 80.0f;


	objects.emplace("rug_corner", new RugCorner());

	objects.emplace("rug", new GameObject());
	objects["rug"]->SetMesh(meshes["rug"]);
	objects["rug"]->SetMaterial(materials["rug"]);
	objects["rug"]->_transform.position = { 24.0f,0.9f,-10.0f }; //1.2 z
	objects["rug"]->_transform.scale *= 0.1f; //0.1f

	objects.emplace("note0", new GameObject());
	objects["note0"]->SetMesh(meshes["cube"]);
	objects["note0"]->SetMaterial(materials["note"]);
	objects["note0"]->_transform.position = { 3.25f,2.5f,-45.2f };
	objects["note0"]->_transform.scale = { 1.5f,1.5f,1.5f };
	objects["note0"]->_transform.rotation.y = -25.0f;

	objects.emplace("note0_interact", new Note(0));
	objects["note0_interact"]->_hitbox = new Hitbox({ 4.2f,1.5f,-44.0f }, { 0.4f,2.5f,2.5f }, true);


	objects.emplace("note1", new GameObject());
	objects["note1"]->SetMesh(meshes["cube"]);
	objects["note1"]->SetMaterial(materials["note"]);
	objects["note1"]->_transform.position = { 39.0f,5.4f,-32.5f };
	objects["note1"]->_transform.scale = { 1.5f,0.001f,1.5f };
	objects["note1"]->_transform.rotation.y = -70.0f;

	objects.emplace("note1_interact", new Note(1));
	objects["note1_interact"]->_hitbox = new Hitbox({ 38.5f,5.5f,-31.0f }, { 1.5f,0.4f,1.5f }, true);

	btn_start.SetOnClick(start_click);
	btn_copy.SetOnClick(copy_click);


	int current = 0;

	//LOADING MATERIALS
	//LOADING MESHES
	//LOADING OBJECTS

	volt::Vec2 size = { (float)env.window->getSize().width, (float)env.window->getSize().height };

	volt::Quad loading_bar({ size.width * 0.02f,size.height * 0.02f }, { 0.0f, size.height * 0.05f }, {18.0f/255.0f,134.0f/255.0f,168.0f/255.0f,1.0f});

	

	for (auto [name, obj] : objects) {
		current++;
		obj->Draw(*env.window);
		loading_text.setText("Loading objects: " + std::to_string(current) + "/" + std::to_string(objects.size()));
		loading_text.Update(env);
		loading_text.Draw(*env.window);
		loading_bar.size.width = ((float)current / (float)objects.size()) * size.width * 0.96;
		env.window->drawQuad(loading_bar, SEPERATE);

		env.window->update();
	}

	//env.window->setBackgroundColour({ 0.55f,0.8f,0.95f,1.0f });
	env.window->setBackgroundColour({ 0.0f,0.0f,0.0f,1.0f });

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float, std::milli> duration = end - start;
}

void MurderMystery::LocalUpdate(Environment& env) {
	GameObject::lbl_name.Update(env);
	GameObject::lbl_action.Update(env);


	murder_mystery_data* data = (murder_mystery_data*)state;

	Room::LocalUpdate(env);

	if (env.window->isKeyJustPressed(volt::Keys::I)) {
		paused = !paused;
		inventory_open = !inventory_open;
	}

	if (data->playing && !paused) {
		env.window->lockCursor();
		for (auto it = players.begin(); it < players.end(); it++) {
			(*it)->Update(env);
			if ((*it)->_transform.position.x <= -1.0f) {
				Json send;
				send.AddPair("action", "update");
				send.AddPair("token", env.token);
				send.AddPair("code", env.code);
				send.AddPair("message", "victory");

				env.server->Send(send);
			}
		}
	}
	else {
		env.window->unlockCursor();
		if (inventory_open) {
			GameObject::lbl_name.setText("Inventory");
			GameObject::lbl_name.Draw(*env.window);
			inventory.Draw(*env.window);
		}
	}

	if (data->playing) {



		Cabinet* cabinet = (Cabinet*)objects["cabinet"];
		cabinet->SetDrawerState(0, data->cabinet_drawers[0]);
		cabinet->SetDrawerState(1, data->cabinet_drawers[1]);

		Desk* desk = (Desk*)objects["desk"];
		for (int i = 0; i < 9; i++) {

			desk->SetDrawerState(i, data->desk_drawers[i]);
		}

		if (data->chest_open) {
			((Chest*)objects["chest_interact"])->Update(env);
			exclude.push_back("chest");
			exclude.push_back("chest_interact");
		}

		if (data->drill_found || !data->safe_open) {
			exclude.push_back("drill");
			exclude.push_back("drill_interact");
			if (data->drill_found && !inventory.HasItem("Drill")) {
				inventory.AddItem("Drill", "A drill, could be used to fix something.", "resources/textures/thumbnails/drill.png");
			}
		}

		if (data->carpet_moved) {
			objects["rug"]->_transform.position.z = -1.2f;
		}

		if (!data->carpet_moved) {
			exclude.push_back("safe");
		}


		if (data->desk_key_found && !inventory.HasItem("Old Key")) {
			inventory.AddItem("Old Key", "An old key. Could be used to open some kind of drawer.", "resources/textures/thumbnails/old_key.png");
		}

		if (data->screws_found && !inventory.HasItem("Screws")) {
			inventory.AddItem("Screws", "A set of screws. Could be used to fix something.", "resources/textures/thumbnails/screws.png");
		}

		if (data->chest_open && !inventory.HasItem("Photo")) {
			inventory.AddItem("Photo", "", "resources/textures/thumbnails/photo0.png");
			inventory.AddItem("Photo", "", "resources/textures/thumbnails/photo1.png");
			inventory.AddItem("Photo", "", "resources/textures/thumbnails/photo2.png");
		}

		if (data->note_found[0]) {
			exclude.push_back("note0");
			exclude.push_back("note0_interact");
			if (!inventory.HasItem("Note")) {
				inventory.AddItem("Note", "A note written on a piece of paper. Might be a clue for escaping this room. Transcript: 'Fix Door 1971'", "resources/textures/thumbnails/note0.png");
			}
		}

		if (!data->desk_drawers[0] || data->note_found[1]) {
			if (data->note_found[1]) {
				if (!inventory.HasItem(" Note ")) {
					inventory.AddItem(" Note ", "A note written on a piece of paper. Might be a clue for escaping this room. Transcript: 'Revise #325'", "resources/textures/thumbnails/note1.png");
				}
			}
			exclude.push_back("note1");
			exclude.push_back("note1_interact");

		}

		if (!data->desk_drawers[0]) {
			exclude.push_back("chest");
			exclude.push_back("chest_interact");
		}


		for (auto [name, obj] : objects) {
			if (std::find(exclude.begin(), exclude.end(), name) == exclude.end()) {
				obj->Update(env);
			}
		}

	}
	else {
		if (data->victory) {
			if (lbl_time_taken.getText() == "") {
				long long remaining = data->end_time - std::time(nullptr);
				remaining = 3600 - remaining;

				unsigned int minutes = remaining / ((long long)60);
				unsigned int seconds = remaining - ((long long)minutes * 60);

				std::string str_minutes = std::to_string(minutes);
				std::string str_seconds = std::to_string(seconds);

				if (str_minutes.length() < 2) {
					str_minutes.insert(0, 2 - str_minutes.length(), '0');
				}

				if (str_seconds.length() < 2) {
					str_seconds.insert(0, 2 - str_seconds.length(), '0');
				}

				lbl_time_taken.setText("Time taken: " + str_minutes + ":" + str_seconds);
			}

			lbl_time_taken.Update(env);
			lbl_victory.Update(env);
			btn_quit.Update(env);

		}
		else {
			if (players.size() >= min_players && players[0]->GetName() == username) {
				btn_start.Update(env);
			}
			lbl_scenario.Update(env);

			if (players.size() < min_players) {
				lbl_waiting.setText("Waiting for players " + std::to_string(players.size()) + "/" + std::to_string(max_players));
			}
			else {
				lbl_waiting.setText("Waiting for host " + std::to_string(players.size()) + "/" + std::to_string(max_players));
			}

			lbl_waiting.Update(env);
			main_panel.Update(env);
			side_panel.Update(env);
			lbl_title.Update(env);
			lbl_code.Update(env);
			btn_copy.Update(env);

			std::string players_str;

			for (auto it = players.begin(); it < players.end(); it++) {
				std::string name = (*it)->GetName();

				players_str += name + " ";

				if (players[0]->GetName() == name) {
					players_str += "(host) ";
				}
				else {
					players_str += " ";
				}

			}

			lbl_players_list.setText(players_str);
			lbl_players_list.Update(env);
		}
		

	}



	
}

void MurderMystery::Draw(volt::Window& window) {
	murder_mystery_data* data = (murder_mystery_data*)state;

	if (data->playing) {
		for (auto it = players.begin(); it < players.end(); it++) {
			if ((*it)->GetName() != username) {
				(*it)->Draw(window);
			}
		}

		for (auto [name, obj] : objects) {
			if (window.isKeyDown(volt::Keys::J)) {
				obj->DrawHitbox(window);
			}
			else {
				if (std::find(exclude.begin(), exclude.end(), name) == exclude.end()) {
					obj->Draw(window);
				}
			}

			
		}


	
	}
	else {		
		if (data->victory) {
			lbl_victory.Draw(window);
			lbl_time_taken.Draw(window);
			btn_quit.Draw(window);
		}
		else {
			volt::Quad screen_quad({ 0.0f,0.0f }, { (float)window.getSize().width, (float)window.getSize().height }, { 0.1f,0.1f,0.1f,1.0f });
			window.drawQuad(screen_quad, SEPERATE);
			main_panel.Draw(window);
			side_panel.Draw(window);

			lbl_scenario.Draw(window);
			lbl_waiting.Draw(window);

			lbl_players_list.Draw(window);
			lbl_title.Draw(window);
			lbl_code.Draw(window);
			btn_copy.Draw(window);

			if (players.size() >= min_players && players[0]->GetName() == username) {
				btn_start.Draw(window);
			}
		}
		
	}

	Room::Draw(window);

	exclude.clear();
}