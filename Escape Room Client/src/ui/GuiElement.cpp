#include "ui/GuiElement.hpp"
#include <sstream>

GuiElement::GuiElement(const std::string& style) : _pos(0.0f,0.0f), _size(0.0f,0.0f), _colour(1.0f,1.0f,1.0f,1.0f), _style(style) {

}

GuiElement::~GuiElement() {

}

void GuiElement::SetStyle(const std::string& style) {
	_style = style;
}

void GuiElement::Update(Environment& env) {

	Split split(_style);

	if (!split.data.empty()) {
		for (auto [attribute, value] : split.data) {
			if (attribute == "width") {
				if (value.substr(value.length() - 2) == "px") {
					_size.x = std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(value.length() - 1) == "%") {
					_size.x = env.window->getSize().x* (std::stof(value.substr(0, value.length() - 1)) / 100.0f);
				}
			}
			else if (attribute == "height") {
				if (value.substr(value.length() - 2) == "px") {
					_size.y = std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(0, 5) == "width") {
					if (value.length() > 5) {
						if (value.substr(value.length() - 1) == "%") {
							_size.y = _size.x * std::stof(value.substr(6, value.length() - 1)) / 100.0f;
						}
						
					}
					else {
						_size.y = _size.x;
					}
				}
				else if (value.substr(value.length() - 1) == "%") {
					_size.y= env.window->getSize().y * (std::stof(value.substr(0, value.length() - 1)) / 100.0f);
				}
			}
			else if (attribute == "left") {
				if (value.substr(value.length() - 2) == "px") {
					_pos.x = std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(value.length() - 1) == "%") {
					_pos.x = env.window->getSize().x * (std::stof(value.substr(0, value.length() - 1)) / 100.0f);
				}
				else if (value == "center") {
					_pos.x = ((float)env.window->getSize().x / 2.0f) - (_size.x / 2.0f);
				}
			}
			else if (attribute == "right") {
				if (value.substr(value.length() - 2) == "px") {
					_pos.x = env.window->getSize().x - std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(value.length() - 1) == "%") {
					_pos.x = env.window->getSize().x - (env.window->getSize().x * (std::stof(value.substr(0, value.length() - 1)) / 100.0f));
				}
			}
			else if (attribute == "top") {
				if (value.substr(value.length() - 2) == "px") {
					_pos.y = env.window->getSize().y - std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(value.length() - 1) == "%") {
					_pos.y = env.window->getSize().y - (env.window->getSize().y * (std::stof(value.substr(0, value.length() - 1)) / 100.0f));
				}
			}
			else if (attribute == "bottom") {
				if (value.substr(value.length() - 2) == "px") {
					_pos.y = std::stof(value.substr(0, value.length() - 2));
				}
				else if (value.substr(value.length() - 1) == "%") {
					_pos.y = env.window->getSize().y * (std::stof(value.substr(0, value.length() - 1)) / 100.0f);
				}
			}
			else if (attribute == "colour") {
				if (value.substr(0, 1) == "#") {
					value = value.substr(1);
				}
				_colour = MakeColour(value);
			}
		}
	}

}

volt::Vec4 GuiElement::MakeColour(const std::string & value) {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;

	if (value.length() < 2) {
		return { r,g,b,a };
	}

	r = (float)std::stoul(value.substr(0, 2), nullptr, 16) / 255.0f;

	if (value.length() >= 4) {
		g = (float)std::stoul(value.substr(2, 2), nullptr, 16) / 255.0f;
	}

	if (value.length() >= 6) {
		b = (float)std::stoul(value.substr(4, 2), nullptr, 16) / 255.0f;
	}

	if (value.length() >= 8) {
		a = (float)std::stoul(value.substr(6, 2), nullptr, 16) / 255.0f;
	}

	return { r,g,b,a };


}

void GuiElement::Draw(volt::Window& window) {
	if (_colour.a > 0.0f) {
		volt::Quad q(_pos, _size, _colour);
		window.drawQuad(q, SEPERATE);
	}

}

Split::Split(const std::string& _data) {
	std::stringstream ss(_data);
	std::string section;

	while (std::getline(ss, section, ';'))
	{
		size_t loc = section.find(":");
		data.push_back(std::make_pair<std::string, std::string>(section.substr(0, loc), section.substr(loc+1)));
	}
}
