#pragma once
#include "scenes/CreateAccount.hpp"

#include "core/Network.hpp"
#include "core/Util.hpp"

void SubmitClick(Button* btn, Environment& env) {
	CreateAccount* scene = (CreateAccount*)env.scene;

	std::unordered_map<std::string, std::string> param;
	param["username"] = scene->username.getText();
	param["password"] = scene->password.getText();

	std::string out = Network::HttpRequest("https://student.csc.liv.ac.uk/~sgkbaker/room/sign_up.php", RequestType::POST, param);

	Json data = Util::JsonParse(out);

	if (data.GetValue("status") == "success") {
		env.token = data.GetValue("token");
		env.scene = Scene::Get("Home");
		env.username = scene->username.getText();
	}
}

CreateAccount::CreateAccount() : Scene(),
username("width: 40%;height: 15%;left: 30%;bottom: 60%;text-align:left;text-size: 40px;", ""),
password("width: 40%;height: 15%;left: 30%;bottom: 42%;text-align:left;text-size: 40px;type:password;", ""),
submit("Sign up", "width: 30%;height: 10%;left: 35%;bottom: 30%;text-align:center;text-size: 48px;")
{
	submit.SetOnClick(SubmitClick);
}

void CreateAccount::Update(Environment& env) {

	username.Update(env);
	password.Update(env);
	submit.Update(env);

}

void CreateAccount::Draw(volt::Window& window) {
	username.Draw(window);
	password.Draw(window);
	submit.Draw(window);
}