#include "scenes/Settings.hpp"
#pragma once

bool Settings::is_fullscreen = true;
bool Settings::sound_enabled = true;

void Settings::BtnBackClick(Button* btn, Environment& env) {
	env.scene = Scene::Get("Home");
}

void Settings::BtnSoundClick(Button* btn, Environment& env) {
	if (sound_enabled) {
		sound_enabled = false;
		btn->setText("Off");
	}
	else {
		sound_enabled = true;
		btn->setText("On");
	}
}

void Settings::BtnFullscreenClick(Button* btn, Environment& env) {
	if (is_fullscreen) {
		is_fullscreen = false;
		env.window->setSize({ 1280,720 });
	}
	else {
		is_fullscreen = true;
		env.window->setSize({});
	}
}

Settings::Settings() : Scene(),
btn_back("Back", "width: 10%;height: 8%;left: 1%;bottom: 90%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"), 
btn_fullscreen("Fullscreen", "width: 40%;height: 15%;left: 30%;bottom: 60%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
btn_sound("On", "width: 20%;height: 12%;left: 50%;bottom: 30%;text-align:center;text-size:auto 70%;text-colour:#FFFFFF;colour:#00000000;hover colour:#1286A8;"),
lbl_sound("Sound: ", "width: 15%;height: 12%;left: 30%;bottom: 30%;text-align:left;text-size:auto 100%;text-colour:#FFFFFF;colour:#00000000;") {
	btn_back.SetOnClick(BtnBackClick);
	btn_fullscreen.SetOnClick(BtnFullscreenClick);
	btn_sound.SetOnClick(BtnSoundClick);
}

void Settings::Update(Environment& env) {
	btn_back.Update(env);
	btn_fullscreen.Update(env);
	btn_sound.Update(env);
	lbl_sound.Update(env);
}

void Settings::Draw(volt::Window& window) {
	btn_back.Draw(window);
	btn_fullscreen.Draw(window);
	btn_sound.Draw(window);
	lbl_sound.Draw(window);
}


