#pragma once

#include "Label.hpp"

class InputField : public Label {
private:
	std::string _hint;
	static InputField* selected;
	static bool show_cursor;
	bool _just_clicked;
	unsigned int _max_characters;
	bool _is_password;
	static int count;

public:
	InputField(const std::string& style, const std::string& hint = "");

	void Update(Environment& env);
	void Draw(volt::Window& window);

	static void InputCallback(unsigned char c);
};