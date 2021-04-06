#pragma once

#include "GuiElement.hpp"

class Label : public GuiElement {
protected:
	std::string _text;
	unsigned long long _font;
	int _text_size;
	int _text_align;
	volt::Vec4 _text_colour;
public:
	Label(const std::string& text, const std::string& style);
	virtual ~Label() = default;

	virtual void Update(Environment& env);
	virtual void Draw(volt::Window& window);

	const std::string& getText();
};