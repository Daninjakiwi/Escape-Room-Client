#pragma once

#include "core/Player.hpp"
#include "scenes/GameScene.hpp"

volt::iVec2 old_pos(0.0f, 0.0f);
bool first = true;
const float sens = 0.15f;

Player::Player(const std::string& username) : name(username), velocity(0.0f, 0.0f, 0.0f), camera() {
	_transform.rotation.y = -90.0f;
	_transform.position = { 0.0f,2.5f,5.0f };
	//camera.translate({ 0.0f,1.0f,5.0f });
}

std::string& Player::GetName() {
	return name;
}

void Player::Update(Environment& env) {

	if (name == env.username) {
		volt::iVec2 pos = env.window->getMousePos();

		if (first) {
			old_pos = pos;
			first = false;
		}

		float xoffset = (pos.x - old_pos.x) * sens;
		float yoffset = (pos.y - old_pos.y) * sens;

		old_pos = pos;

		_transform.rotation.y += xoffset;
		_transform.rotation.x += yoffset;

		if (_transform.rotation.x > 89.0f) {
			_transform.rotation.x = 89.0f;
		}
		else if (_transform.rotation.x < -89.0f) {
			_transform.rotation.x = -89.0f;
		}

		if (_transform.rotation.y >= 270.0f) {
			_transform.rotation.y = -90.0f;
		}
		else if (_transform.rotation.y < -90.0f) {
			//_transform.rotation.y = -90.0f;
			_transform.rotation.y = 270.0f;
		}

		//std::cout << _transform.rotation.y + 90.0f << std::endl;

		//modff(_transform.rotation.y + 90.0f, 360.0f);

		float rot = _transform.rotation.y + 90.0f;


		//std::cout <<  volt::maths::cosd(rot) << std::endl;

		velocity = {};

		//td::cout << volt::maths::sind(rot + 90.0f) << std::endl;

		if (env.window->isKeyDown(volt::Keys::W)) {

			velocity.z -= volt::maths::cosd(rot) * 8.0f * env.window->getDelta();
			velocity.x += volt::maths::sind(rot) * 8.0f * env.window->getDelta();
		} 

		if (env.window->isKeyDown(volt::Keys::S)) {
			velocity.z += volt::maths::cosd(rot) * 4.0f * env.window->getDelta();
			velocity.x -= volt::maths::sind(rot) * 4.0f * env.window->getDelta();
		}

		if (env.window->isKeyDown(volt::Keys::A)) {
			velocity.z += volt::maths::cosd(rot + 90.0f) * 6.0f * env.window->getDelta();
			velocity.x -= volt::maths::sind(rot + 90.0f) * 6.0f * env.window->getDelta();
		}

		if (env.window->isKeyDown(volt::Keys::D)) {
			velocity.z -= volt::maths::cosd(rot + 90.0f) * 6.0f * env.window->getDelta();
			velocity.x += volt::maths::sind(rot + 90.0f) * 6.0f * env.window->getDelta();
		}

		_transform.position += velocity;

		

	}

	camera.setRotation(_transform.rotation);
	camera.setPosition(_transform.position);

	env.window->setViewMatrix(camera);

}

void Player::Draw(volt::Window& window) {

}