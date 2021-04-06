#pragma once
#include <vector>
#include <string>
#include "core/Environment.hpp"
#include "core/Util.hpp"
#include "ui/Label.hpp"
#include "core/GameObject.hpp"
#include "core/Player.hpp"

struct reserved_state {
	bool playing; //Is the game being played
	bool victory; //Has the game been won
	long long end_time;
};

class Room {
	friend class Player;
	friend class wall;
private:
	unsigned int byte_count;
	Label announcement;
	Label timer;

protected:
	std::vector<Player> players;
	std::unordered_map<std::string, GameObject*> objects;
	std::unordered_map<std::string, volt::Mesh*> meshes;
	std::unordered_map<std::string, volt::Material*> materials;
	void* state;
public:
	Room(const std::string& data, unsigned int byte_count);
	~Room();

	virtual void LocalUpdate(Environment& env);
	void ServerUpdate(const std::string& message);

	void MakeAnnouncement(const std::string& message, unsigned int duration);

	void* GetState();

	virtual void Draw(volt::Window& window) = 0;
};