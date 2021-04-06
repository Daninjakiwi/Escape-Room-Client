#pragma once

#include "core/Scene.hpp"

std::unordered_map<std::string, Scene*> Scene::scenes;

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Register(const std::string& name, Scene* scene) {
	scenes[name] = scene;
}
Scene* Scene::Get(const std::string& name) {
	return scenes[name];
}
