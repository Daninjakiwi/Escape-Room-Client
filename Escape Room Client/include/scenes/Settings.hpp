#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"

class Settings : public Scene {
private:
	Button btn_back;
	Button btn_fullscreen;
	Button btn_sound;
	Label lbl_sound;
	static bool is_fullscreen;
	static bool sound_enabled;
public:
	Settings();

	void Update(Environment& env);
	void Draw(volt::Window& window);
private:
	static void BtnBackClick(Button* btn, Environment& env);
	static void BtnFullscreenClick(Button* btn, Environment& env);
	static void BtnSoundClick(Button* btn, Environment& env);
};
