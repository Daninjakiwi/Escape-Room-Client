#pragma once

#include "core/GameObject.hpp"
#include "core/UniquePtr.hpp"
#include "ui/Button.hpp"

class Safe : public GameObject {
private:
	static UniquePtr<volt::PbrMaterial> materials[3];
	static volt::Mesh meshes[16];
	static bool is_active;
	static std::string combination;

	bool is_open;
	bool is_looking;
	bool is_unlocked;

	GuiElement panel;
	Button btn_close;
	Button btn_submit;
public:
	Safe();

	void Update(Environment& env);
	void Draw(volt::Window& window);
	void OnLook();
private:
	static void BtnCloseClick(Button* btn, Environment& env);
	static void BtnSubmitClick(Button* btn, Environment& env);
};