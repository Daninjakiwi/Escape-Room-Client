#pragma once

#include "core/Player.hpp"
#include "scenes/GameScene.hpp"

volt::iVec2 old_pos(0.0f, 0.0f);
bool first = true;
const float sens = 0.15f;

Player::Player(const std::string& username) : name(username), velocity(0.0f, 0.0f, 0.0f), camera() {
	_transform.rotation.y = -90.0f;
	_transform.position = { 4.0f,10.0f,-5.0f };
	_transform.scale = { 1.0f,2.5f,1.0 };
	_hitbox = new Hitbox(_transform.position, _transform.scale);
}

std::string& Player::GetName() {
	return name;
}

void Player::Update(Environment& env) {

	Room* room = ((GameScene*)env.scene)->room;

	reserved_state* state = (reserved_state*)room->GetState();

	if (name == env.username) {
		if (state->playing) {
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

			double rot = _transform.rotation.y + 90.0;

			velocity = {};

			if (env.window->isKeyDown(volt::Keys::W)) {

				velocity.z -= volt::maths::cosd(rot) * 8.0f * env.window->getDelta();
				velocity.x += volt::maths::sind(rot) * 8.0f * env.window->getDelta();
			}

			if (env.window->isKeyDown(volt::Keys::S)) {
				velocity.z += volt::maths::cosd(rot) * 4.0f * env.window->getDelta();
				velocity.x -= volt::maths::sind(rot) * 4.0f * env.window->getDelta();
			}

			if (env.window->isKeyDown(volt::Keys::A)) {
				velocity.z += volt::maths::cosd(rot + 90.0) * 6.0f * env.window->getDelta();
				velocity.x -= volt::maths::sind(rot + 90.0) * 6.0f * env.window->getDelta();
			}

			if (env.window->isKeyDown(volt::Keys::D)) {
				velocity.z -= volt::maths::cosd(rot + 90.0) * 6.0f * env.window->getDelta();
				velocity.x += volt::maths::sind(rot + 90.0) * 6.0f * env.window->getDelta();
			}

			velocity.y -= 9.81 * env.window->getDelta();

			//_transform.position += velocity;

			//_transform.position += velocity;
			//_hitbox->position += velocity;

			for (auto [name, obj] : room->objects) {
				_hitbox->position.x += velocity.x;
				if (CollidesWith(*obj)) {
					velocity.x = 0.0f;
				}
				_hitbox->position.x = _transform.position.x;
				_hitbox->position.y += velocity.y;
				if (CollidesWith(*obj)) {
					velocity.y = 0.0f;
				}
				_hitbox->position.y = _transform.position.y;
				_hitbox->position.z += velocity.z;
				if (CollidesWith(*obj)) {
					velocity.z = 0.0f;
				}
				_hitbox->position.z = _transform.position.z;
			}

			_transform.position += velocity;
			_hitbox->position = _transform.position;

			//std::cout << _transform.rotation << std::endl;

			float yaw = _transform.rotation.y + 90.0f;
			float pitch = _transform.rotation.x;

			volt::Vec3 dir;
			dir.x = volt::maths::sind(yaw) * volt::maths::cosd(pitch);
			dir.y = volt::maths::sind(pitch);
			dir.z = -volt::maths::cosd(yaw) * volt::maths::cosd(pitch);

			GameObject temp;
			temp._hitbox = new Hitbox({ _transform.position.x, _transform.position.y + 3.5f, _transform.position.z }, { 0.1f,0.1f,0.1f });

			bool flag = false;

			for (auto [name, obj] : room->objects) {
				for (int i = 0; i < 20; i++) {
					temp._hitbox->position += dir;

					if (temp.CollidesWith(*obj)) {
						obj->OnLook();
						flag = true;
						break;
					}
					
				}

				if (flag) {
					break;
				}

				temp._hitbox->position = { _transform.position.x, _transform.position.y + 3.5f, _transform.position.z };
			}

			

			//std::cout << temp._hitbox->position << std::endl;

		}

		camera.setRotation(_transform.rotation);
		camera.setPosition({ _transform.position.x, _transform.position.y + 3.5f, _transform.position.z });

		env.window->setViewMatrix(camera);
	}


	

}

void Player::Draw(volt::Window& window) {

}