#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"

class CreateAccount : public Scene {
public:
	InputField username, password;
	Button submit, btn_back;
public:
	CreateAccount();

	void Update(Environment& env);
	void Draw(volt::Window& window);
private:
	static void BtnBackClick(Button* btn, Environment& env);
};