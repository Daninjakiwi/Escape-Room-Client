#include "scenes/MainMenu.hpp"
#include "core/Util.hpp"
#include <thread>

#include "scenes/Home.hpp"

void GuestClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Home");

	std::unordered_map<std::string, std::string> data;
	data["password"] = "#<u`xW4Q[w8VG=CX";

	std::string out = Network::HttpRequest("https://student.csc.liv.ac.uk/~sgkbaker/room/auth_guest.php", RequestType::POST, data);

	Json json = Util::JsonParse(out);
	if (json.GetValue("status") == "success") {
		env.token = json.GetValue("token");
		env.username = json.GetValue("username");

		Home* scene = (Home*)env.scene;
		scene->guest = true;


		scene->settings = { scene->settings.getText(), "width: 34%;height: 8%;left: 33%;bottom: 50%;text-align:center;text-size:auto 80%;" };
	}


}

void LoginClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Login");
}

void CreateClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("CreateAccount");
}

void AgainClick(Button* btn, Environment& env) {
	MainMenu* scene = (MainMenu*)env.scene;

	scene->connection_failed = false;
	scene->is_connecting = true;
}

bool MainMenu::server_connected = false;
bool MainMenu::is_connecting = true;
bool MainMenu::connection_failed = false;

MainMenu::MainMenu() : 
	Scene(),
	guest("Play as Guest", "width: 40%;height: 12%;left: 30%;bottom: 55%;text-size:auto 70%;text-align:center;colour:#FFFFFF;hover colour:#CCCCCC;"),
	login("Sign in", "width: 20%;height: 8%;left: 40%;bottom:45%;text-size:auto 70%;text-align:center;"),
	create("Create account", "width: 25%;height: 8%;left: 37.5%;bottom: 35%;text-size:auto 70%;text-align:center;"),
	again("Retry Connection", "width: 20%;height: 5%;left: 40%;bottom: 35%;text-size:auto 90%;text-align:center;"),
	connecting("Connecting to server", "width: 30%;height: 10%;left: 35%;bottom: 45%;text-size:auto 80%;text-align:center;"),
	failed("Failed to connect to server", "width: 40%;height: 10%;left: 30%;bottom: 50%;text-size:auto 70%;text-align:center;")
{
	guest.SetOnClick(GuestClick);
	login.SetOnClick(LoginClick);
	create.SetOnClick(CreateClick);
	again.SetOnClick(AgainClick);
}


struct example_struct {
	unsigned int a;
	unsigned int b;
	bool c;
};


void MainMenu::MessageFeed(const std::string& message) {


	server_connected = true;
}

void MainMenu::AttemptConnection(UdpConnection* server) {
	//UdpConnection server = Network::UdpConnect(ip, port);
	server->ListenForMessages(MessageFeed);
	int attempts = 3;
	while (attempts > 0 && server_connected == false) {
		server->Send("test");
		std::this_thread::sleep_for(std::chrono::seconds(1));
		attempts -= 1;
	}
	if (attempts == 0 && !server_connected) {
		connection_failed = true;
	}
	server->StopMessages();
}


void MainMenu::Update(Environment& env) {
	if (connection_failed) {
		again.Update(env);
		failed.Update(env);
	}

	if (is_connecting) {
		is_connecting = false;
		connecting.Update(env);

		std::string out = Network::HttpRequest("https://student.csc.liv.ac.uk/~sgkbaker/room/server_info.php");

		Json data = Util::JsonParse(out);

		env.ip = data.GetValue("ip");
		env.port = std::stoi(data.GetValue("port"));
		env.server->SetDestination(env.ip, env.port);

		std::thread{ AttemptConnection, env.server }.detach();

	}
	
	if (server_connected) {
		guest.Update(env);
		login.Update(env);
		create.Update(env);
	}
	
		 

}

void MainMenu::Draw(volt::Window& window) {


	if (connection_failed) {
		again.Draw(window);
		failed.Draw(window);
	}
	else if (!server_connected) {
		connecting.Draw(window);
	}


	guest.Draw(window);
	login.Draw(window);
	create.Draw(window);
}