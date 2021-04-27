#pragma once

#include "core/Scene.hpp"
#include "ui/TextureButton.hpp"
#include "ui/Label.hpp"
#include "ui/Button.hpp"

class SelectScenario : public Scene {
private:
	static std::vector<std::string> scenarios;
	Button btn_back;

	std::vector<Button*> buttons;
	std::vector<volt::Texture*> tex;
public:
	SelectScenario(volt::Window& window);
	~SelectScenario();

	void Update(Environment& env);
	void Draw(volt::Window& window);
private:
	static void btn_click(Button* btn, Environment& env);
	static void BtnBackClick(Button* btn, Environment& env);
};
