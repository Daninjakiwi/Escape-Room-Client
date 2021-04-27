#pragma once
#include "Room.hpp"
#include "ui/Button.hpp"
#include "ui/InputField.hpp"
#include "core/GameObject.hpp"
#include "ui/MultiLineLabel.hpp"

struct murder_mystery_data {
	bool playing; //Is the game being played
	bool victory; //Has the game been won
	long long end_time;
	bool desk_drawers[9];
	bool desk_key_found;
	bool desk_unlocked;
	bool cabinet_drawers[2];
	bool cabinet_key_found;
	bool cabinet_unlocked;
	bool safe_unlocked;
	bool safe_open;
	bool carpet_moved;
	bool note_found[2];
	bool screws_found;
	bool chest_open;
	bool drill_found;
	bool door_fixed;
	bool door_open;
};

class MurderMystery : public Room {
private:
	Button btn_start;
	Button btn_copy;
	Button btn_quit;
	MultiLineLabel lbl_scenario;
	MultiLineLabel lbl_players_list;
	Label lbl_title;
	Label lbl_waiting;
	Label lbl_code;
	Label lbl_victory;
	Label lbl_time_taken;
	GuiElement main_panel, side_panel;
	std::vector<std::string> exclude;
public:
	MurderMystery(const std::string& data, Environment& env);

	void LocalUpdate(Environment& env);
	void Draw(volt::Window& window);
};
