#pragma once
#include "core/GameObject.hpp"
#include "ui/Button.hpp"

class Chest : public GameObject {
private:
	static bool is_active;
	static std::string combination;
	bool is_looking;
	GuiElement panel;
	Button btn_close;
	Button btn_left;
	Button btn_right;
	Label lbl_info;
	volt::Texture tex_chest;
public:
	Chest();

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
private:
	static void BtnCloseClick(Button* btn, Environment& env);
	static void BtnLeftClick(Button* btn, Environment& env);
	static void BtnRightClick(Button* btn, Environment& env);
};