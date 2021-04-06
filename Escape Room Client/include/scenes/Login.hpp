#pragma once

#include "core/Scene.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"

class Login : public Scene {
public:
	InputField username, password;
	Button submit;
public:
	Login();

	void Update(Environment& env);
	void Draw(volt::Window& window);
};