#pragma once

#include "Label.hpp"

class Button : public Label {
private:
	void (*_click)(Button*, Environment&);
	bool _just_clicked;
public:
	Button(const std::string& text, const std::string& style);

	void Update(Environment& env);

	void SetOnClick(void (*func)(Button*, Environment&));
};