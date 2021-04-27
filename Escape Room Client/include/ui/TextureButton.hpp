#pragma once

#include "GuiElement.hpp"

class TextureButton : public GuiElement {
private:
	volt::Texture tex;
	bool just_clicked;

	void (*hover_func)(TextureButton*, Environment&);
	void (*click_func)(TextureButton*, Environment&);
public:
	TextureButton(const std::string& path, const std::string& style);

	void Update(Environment& env);
	void Draw(volt::Window& window);

	void SetHoverFunc(void (*func)(TextureButton*, Environment&));
	void SetClickFunc(void (*func)(TextureButton*, Environment&));
};