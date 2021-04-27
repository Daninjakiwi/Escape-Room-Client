#pragma once
#include "Label.hpp"

class MultiLineLabel : public Label {
private:
	int max_words;
public:
	MultiLineLabel(const std::string& text, const std::string& style);

	void Update(Environment& env);
	void Draw(volt::Window& window);
};
