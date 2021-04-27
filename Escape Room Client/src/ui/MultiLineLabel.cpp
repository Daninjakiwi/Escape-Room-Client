#pragma once
#include "ui/MultiLineLabel.hpp"
#include <sstream>

MultiLineLabel::MultiLineLabel(const std::string& text, const std::string& style) : Label(text,style), max_words(0) {

}

void MultiLineLabel::Update(Environment& env) {
	Label::Update(env);

	Split split(_style);

	if (!split.data.empty()) {
		for (auto [attribute, value] : split.data) {
			if (attribute == "max-words") {
				max_words = std::stoi(value);
			}
		}
	}
}
void MultiLineLabel::Draw(volt::Window& window) {
	std::string buffer;

	volt::Font* font = volt::Font::get(_font);

	int line = 0;
	int word_count = 0;

	std::stringstream ss(_text);
	std::string section;

	std::vector<std::string> words;

	while (std::getline(ss, section, ' ')) {
		words.emplace_back(section);
	}



	if (words.size() > 0) {
		for (auto word : words) {
			if (font->widthOf(buffer + " " + word, _text_size) > _size.x || (word_count == max_words && max_words != 0) || word == "\n") {
				window.drawString(buffer, { _pos.x, _pos.y + (_size.y / 2.0f) - (line * _text_size) }, _text_size, _font, _text_colour);
				buffer = "";
				line++;
				word_count = 0;
			}
			if (buffer.length() != 0) {
				buffer += " ";
			}
			buffer += word;
			word_count++;
		}
	}

	if (buffer.length() > 0) {
		window.drawString(buffer, { _pos.x, _pos.y + (_size.y / 2.0f) - (line * _text_size) }, _text_size, _font, _text_colour);
	}

}