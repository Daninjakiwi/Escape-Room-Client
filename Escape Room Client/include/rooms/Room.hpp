#pragma once
#include <vector>
#include <string>
#include "core/Environment.hpp"
#include "core/Util.hpp"
#include "ui/Label.hpp"
#include "core/GameObject.hpp"
#include "core/Player.hpp"

class Room {
	friend class Player;
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
	~Room() = default;

	virtual void LocalUpdate(Environment& env);
	void ServerUpdate(const std::string& message);

	void MakeAnnouncement(const std::string& message, unsigned int duration);

	void* GetState();

	virtual void Draw(volt::Window& window) = 0;
};