#pragma once

#include "core/Scene.hpp"
#include "ui/MultiLineLabel.hpp"
#include "ui/Button.hpp"

class Credits : public Scene {
private:
	Button btn_back;
	MultiLineLabel credits;
public:
	Credits();

	void Update(Environment& env);
	void Draw(volt::Window& window);
private:
	static void BtnBackClick(Button* btn, Environment& env);
};