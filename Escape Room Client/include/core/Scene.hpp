#pragma once
#include "GameObject.hpp"
#include <vector>

class Scene {
private:
	static std::unordered_map<std::string, Scene*> scenes;
public:
	std::vector<GameObject*> objects;

	Scene();

	virtual ~Scene();

	virtual void Update(Environment& env) = 0;
	virtual void Draw(volt::Window& window) = 0;

	static void Register(const std::string& name, Scene* scene);
	static Scene* Get(const std::string& name);
};
