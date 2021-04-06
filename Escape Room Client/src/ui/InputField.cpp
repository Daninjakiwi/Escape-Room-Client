#pragma once

#include <thread>

#include "ui/InputField.hpp"

enum Align {
	LEFT = 0,
	CENTER = 1,
	RIGHT = 2
};

InputField* InputField::selected = nullptr;
bool InputField::show_cursor = false;
int InputField::count = 0;


InputField::InputField(const std::string& style, const std::string& hint) : Label("", style), _hint(hint), _just_clicked(false), _max_characters(0), _is_password(false) {

}

void InputField::Update(Environment& env) {
	Label::Update(env);

	Split split(_style);

	if (!split.data.empty()) {
		for (auto [attribute, value] : split.data) {
			if (attribute == "max-length") {
				_max_characters = std::stoi(value);
			}
			else if (attribute == "type") {
				if (value == "text") {
					_is_password = false;
				}
				else if (value == "password") {
					_is_password = true;
				}
			}
		}
	}

	volt::iVec2 mouse = env.window->getMousePos();

	if (_just_clicked && !env.window->isMouseDown()) {
		_just_clicked = false;
	}
	if (env.window->isMouseDown()) {
		if (mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y) {
			if (!_just_clicked && env.window->isMouseJustPressed()) {
				selected = this;
				env.window->setCharCallback(InputCallback);
				_just_clicked = true;
				count = 0;
			}

		}
		else {

			if (selected == this) {

				selected = nullptr;
				env.window->setCharCallback(nullptr);
				show_cursor = false;
			}

		}
	}

	if (selected == this) {
		count += 1;
		double delta = env.window->getDelta();
		double fps = 1.0 / delta;

		if (count > fps) {
			show_cursor = false;
			count = 0;
		}
		else if (count > fps / 2.0) {
			show_cursor = true;
		}
	}
	
}

void InputField::Draw(volt::Window& window) {
	GuiElement::Draw(window);

	volt::Font* font = volt::Font::get(_font);

	std::string replaced;

	if (_is_password) {
		for (int i = 0; i < _text.length(); i++) {
			replaced += "*";
		}
	}
	else {
		replaced = _text;
	}

	std::string temp = replaced;

	if (show_cursor && selected == this) {
		temp += "|";
	}

	if (_text_align == Align::LEFT) {
		window.drawString(temp, { _pos.x, _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}
	else if (_text_align == Align::CENTER) {

		float w = font->widthOf(replaced, _text_size);
		window.drawString(temp, { _pos.x + ((_size.x - w) / 2.0f), _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}
	else if (_text_align == Align::RIGHT) {
		window.drawString(temp, { _pos.x + _size.x - font->widthOf(replaced, _text_size), _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}

}

void InputField::InputCallback(unsigned char c) {
	if (c == 8) {
		std::string& t = selected->_text;
		t = t.substr(0, t.length() - 1);
	}
	else {
		if (selected->_text.length() < selected->_max_characters || selected->_max_characters == 0) {
			selected->_text += c;
		}

	}
}
