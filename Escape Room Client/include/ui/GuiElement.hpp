#pragma once
#include <Volt.hpp>
#include "core/Environment.hpp"

class GuiElement {
	friend class SelectScenario;
protected:
	volt::Vec2 _pos, _size;
	volt::Vec4 _colour;
	std::string _style;
public:
	GuiElement(const std::string& style);
	virtual ~GuiElement();

	virtual void Update(Environment& env);
	virtual void Draw(volt::Window& window);

	void SetStyle(const std::string& style);

protected:
	volt::Vec4 MakeColour(const std::string& value);
};

class Split {
public:
	std::vector<std::pair<std::string, std::string>> data;

	Split(const std::string& _data);
};