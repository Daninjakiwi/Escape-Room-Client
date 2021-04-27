#include "scenes/Login.hpp"


#include "core/Network.hpp"
#include "core/Util.hpp"

void submitClick(Button* btn, Environment& env) {
	Login* scene = (Login*)env.scene;

	std::unordered_map<std::string, std::string> param;
	param["username"] = scene->username.getText();
	param["password"] = scene->password.getText();

	std::string out = Network::HttpRequest("https://student.csc.liv.ac.uk/~sgkbaker/room/auth.php", RequestType::POST, param);

	Json data = Util::JsonParse(out);

	if (data.GetValue("status") == "success") {
		env.token = data.GetValue("token");
		env.scene = Scene::Get("Home");
		env.username = scene->username.getText();

		scene->error.setText("");
	}
	else {
		scene->error.setText("Invalid Username/Password");
	}
}

void Login::BtnBackClick(Button* btn, Environment& env) {
	Login* scene = (Login*)env.scene;
	scene->error.setText("");

	env.scene = Scene::Get("MainMenu");
}

Login::Login() : Scene(),
username("width: 40%;height: 15%;left: 30%;bottom: 60%;text-align:left;text-size: 0.06h;text-colour:#FFFFFF;colour:#303030FF;", "Username"),
password("width: 40%;height: 15%;left: 30%;bottom: 42%;text-align:left;text-size: 0.06h;type:password;text-colour:#FFFFFF;colour:#303030FF;", "Password"),
submit("Submit", "width: 30%;height: 10%;left: 35%;bottom: 25%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
error("", "width: 50%;height: 15%;left: 25%;bottom: 80%;text-align:center;text-size:auto 70%;text-colour:#FF0000;colour:#00000000;"),
btn_back("Back", "width: 10%;height: 8%;left: 1%;bottom: 90%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;")
{
	submit.SetOnClick(submitClick);
	btn_back.SetOnClick(BtnBackClick);

}

void Login::Update(Environment& env) {

	username.Update(env);
	password.Update(env);
	submit.Update(env);
	error.Update(env);

	btn_back.Update(env);



}

void Login::Draw(volt::Window& window) {
	username.Draw(window);
	password.Draw(window);
	submit.Draw(window);
	btn_back.Draw(window);

	if (error.getText() == "Invalid Username/Password") {
		error.Draw(window);
	}

}