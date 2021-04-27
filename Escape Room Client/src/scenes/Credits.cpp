#pragma once
#include "scenes/Credits.hpp"

void Credits::BtnBackClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("MainMenu");
}

Credits::Credits() : Scene(), 
btn_back("Back", "width: 10%;height: 8%;left: 1%;bottom: 90%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"), 
credits("All textures used are licensed under the Creative Commons 0 license. \n \n \n All Models used are licensed under the Creative Commons 0 license.", "width: 80%;left: 3%;bottom: 82%;text-align:left;text-size:0.06h;text-colour:#FFFFFF;") {
	btn_back.SetOnClick(BtnBackClick);
}

void Credits::Update(Environment& env) {
	btn_back.Update(env);
	credits.Update(env);
}

void Credits::Draw(volt::Window& window) {
	btn_back.Draw(window);
	credits.Draw(window);
}
