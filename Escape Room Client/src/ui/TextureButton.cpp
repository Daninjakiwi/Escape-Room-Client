
#pragma once
#include "ui/TextureButton.hpp"

TextureButton::TextureButton(const std::string& path, const std::string& style) : GuiElement(style), tex(), hover_func(nullptr), click_func(nullptr), just_clicked(false) {
	tex.init(path);
}

void TextureButton::Update(Environment& env) {
	GuiElement::Update(env);

	volt::iVec2 mouse = env.window->getMousePos();
	if (mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y) {
		if (hover_func) {
			hover_func(this, env);
		}

		if (env.window->isMouseJustPressed()) {
			if (click_func != nullptr && just_clicked == false) {
				just_clicked = true;
				click_func(this, env);
			}
		}
		else {
			just_clicked = false;
		}
	}
}

void TextureButton::Draw(volt::Window& window) {
	window.drawTexture(tex, _pos, _size);
}

void TextureButton::SetHoverFunc(void (*func)(TextureButton*, Environment&)) {
	hover_func = func;
}

void TextureButton::SetClickFunc(void (*func)(TextureButton*, Environment&)) {
	click_func = func;
}

