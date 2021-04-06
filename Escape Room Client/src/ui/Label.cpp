#pragma once

#include "ui/Label.hpp"

enum Align {
	LEFT = 0,
	CENTER = 1,
	RIGHT = 2
};


Label::Label(const std::string& text, const std::string& style) : GuiElement(style),
_text(text), _font(volt::fonts::SEGOE), _text_size(16), _text_align(0), _text_colour(0.0f,0.0f,0.0f,1.0f)
{

}

void Label::Update(Environment& env) {
	GuiElement::Update(env);

	Split split(_style);

	if (!split.data.empty()) {
		for (auto [attribute, value] : split.data) {
			if (attribute == "text-align") {
				if (value == "left") {
					_text_align = Align::LEFT;
				}
				else if (value == "center") {
					_text_align = Align::CENTER;
				}
				else if (value == "right") {
					_text_align = Align::RIGHT;
				}
			}
			else if (attribute == "font") {
				//Implement when more fonts added
			}
			else if (attribute == "text-size") {
				if (value.length() >= 4 && value.substr(0, 4) == "auto") {
					float scale = 0.5f;
					if (value.size() > 5) {
						if (value.substr(value.length() - 1) == "%") {
							scale = (float)std::stoi(value.substr(5, value.length() - 6)) / 100.0f;
						}

						if (value.substr(5) == "large") {
							scale = 0.8f;
						}
						else if (value.substr(5) == "small") {
							scale = 0.3f;
						}
					}

					bool flag = false;
					int new_size = 1;
					volt::Font* font = volt::Font::get(_font);
					if (_text.length() != 0) {
						while (!flag) {
							if (font->widthOf(_text, new_size) < _size.x * scale) {
								new_size += 1;
							}
							else if (font->widthOf(_text, new_size) >= _size.x * scale) {
								flag = true;
							}
						}
					}

					if (new_size > _size.y) {
						new_size = _size.y;
					}
					_text_size = new_size;
				}
				else {
					if (value.substr(value.length() - 2, 2) == "px") {
						_text_size = std::stoi(value);
					}
				}
			}
			else if (attribute == "text-colour") {
				if (value.substr(0, 1) == "#") {
					value = value.substr(1);
				}
				_text_colour = MakeColour(value);
			}
		}
	}
}

void Label::Draw(volt::Window& window) {
	GuiElement::Draw(window);

	volt::Font* font = volt::Font::get(_font);


	if (_text_align == Align::LEFT) {
		window.drawString(_text, { _pos.x, _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}
	else if (_text_align == Align::CENTER) {

		float w = font->widthOf(_text, _text_size);
		window.drawString(_text, { _pos.x + ((_size.x - w) / 2.0f), _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}
	else if (_text_align == Align::RIGHT) {
		window.drawString(_text, { _pos.x + _size.x - font->widthOf(_text, _text_size), _pos.y + (_size.y / 2.0f) }, _text_size, _font, _text_colour);
	}

}

const std::string& Label::getText() {
	return _text;
}