#include "ui/Button.hpp"

Button::Button(const std::string& text, const std::string& style) : Label(text,style), _click(nullptr), _just_clicked(false) {
}

void Button::Update(Environment& env) {
	Label::Update(env);

	volt::iVec2 mouse = env.window->getMousePos();
	if (mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y) {

		std::string type = "hover";

		if (env.window->isMouseJustPressed()) {
			type = "click";
			if (_click != nullptr && _just_clicked == false) {
				_just_clicked = true;
				_click(this, env);
			}
		}
		else {
			_just_clicked = false;
		}

		std::string original = _style;

		Split split(_style);

		if (!split.data.empty()) {
			for (auto [attribute, value] : split.data) {
				if (attribute.substr(0, 5) == type) {
					_style += attribute.substr(6) + ":" + value + ";";
				}
			}
		}

		Label::Update(env);

		_style = original;
	}
}
void Button::SetOnClick(void (*func)(Button*, Environment&)) {
	_click = func;
}
