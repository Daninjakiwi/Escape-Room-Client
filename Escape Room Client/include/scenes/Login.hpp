#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"

class Login : public Scene {
public:
	InputField username, password;
	Button submit;
	Label error;
	Button btn_back;
public:
	Login();

	void Update(Environment& env);
	void Draw(volt::Window& window);
private:
	static void BtnBackClick(Button* btn, Environment& env);
};