#include <iostream>
#include <thread>
#include <Volt.hpp>

#include "scenes/GameScene.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/Login.hpp"
#include "scenes/CreateAccount.hpp"
#include "scenes/Home.hpp"

#include "core/Network.hpp"
#include "core/Util.hpp"
#include <render/stb_image.h>

int main() {

	Network::Initialise();

	volt::Window window("Escape Room", { 1280,720 });

	window.setSize({ 1280,720 });

	window.createContext(volt::ContextType::OPENGL);

	window.setBackgroundColour({ 0.4,0.4,0.38f,1.0f });

	window.loadEnvironmentMap("resources/images/street_4k.hdr");

	stbi_set_flip_vertically_on_load(true);
	int width, height, bpp;
	float* data = stbi_loadf("resources/images/street_4k.hdr", &width, &height, &bpp, 0);

	volt::Texture tex;
	tex.init(data, { width, height });

	stbi_image_free(data);

	volt::DynamicTexture::setQuality(volt::Quality::ULTRA);

	volt::Camera cam;
	cam.translate({ 0.0f,1.0f,5.0f });

	window.setViewMatrix(cam);

	const float speed = 5.0f;

	MainMenu main_menu_scene;
	GameScene game_scene;
	Login login_scene;
	CreateAccount create_account_scene;
	Home home_scene;

	Scene::Register("MainMenu", &main_menu_scene);
	Scene::Register("Game", &game_scene);
	Scene::Register("Login", &login_scene);
	Scene::Register("CreateAccount", &create_account_scene);
	Scene::Register("Home", &home_scene);

	Environment env;
	env.server = new UdpConnection("0.0.0.0", 0); 

	env.window = &window;
	env.scene = Scene::Get("MainMenu");

	while (window) {

		if (window.isKeyDown(volt::Keys::W)) {
			cam.translate({ 0.0f, 0.0f,-speed * (float)window.getDelta() });
		}

		if (window.isKeyDown(volt::Keys::S)) {
			cam.translate({ 0.0f,0.0f,speed * (float)window.getDelta()});
		}

		if (window.isKeyDown(volt::Keys::D)) {
			cam.translate({speed * (float)window.getDelta(),0.0f, 0.0f });
		}

		if (window.isKeyDown(volt::Keys::A)) {
			cam.translate({-speed * (float)window.getDelta(),0.0f, 0.0f });
		}

		if (window.isKeyDown(volt::Keys::Q)) {
			cam.rotate({0.0f, speed * 4.0f * (float)window.getDelta(),0.0f });
		}

		if (window.isKeyDown(volt::Keys::E)) {
			cam.rotate({ 0.0f, -speed * 4.0f * (float)window.getDelta(),0.0f });
		}

		if (window.isKeyDown(volt::Keys::G)) {
			system("cls");
		}

		//std::cout << window.getMousePos().y << std::endl;

		//window.setViewMatrix(cam.getView());

		//std::cout << 1.0 / window.getDelta() << std::endl;


		((Scene*)env.scene)->Update(env);
		((Scene*)env.scene)->Draw(window);
		//window.drawTexture(tex, { 100,100 }, { 512,512 });


		window.update();
	}

	Network::Terminate();

	
}