#pragma once

#include "core/Player.hpp"
#include "scenes/GameScene.hpp"

volt::iVec2 old_pos;
bool first = true;
const float sens = 0.1f;

volt::Vec3 last_sent;
volt::Vec3 last_rot;

Player::Player(const std::string& username) : name(username), velocity(0.0f, 0.0f, 0.0f), camera() {
_transform.rotation.y = 150.0f;
_transform.position = { 47.0f,5.0f,-47.0f };
_transform.scale = { 3.0f,8.5f,3.0f };
_hitbox = new Hitbox(_transform.position, { 2.5f,4.0f,2.5f });
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

			float delta = env.window->getDelta();

			if (delta > 0.06f) {
				delta = 0.06f;
			}

			if (first) {
				old_pos = pos;
				last_sent = _transform.position;
				last_rot = _transform.rotation;
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
				_transform.rotation.y = 270.0f;
			}

			double rot = _transform.rotation.y + 90.0;

			velocity = {};

			if (env.window->isKeyDown(volt::Keys::W)) {
				
				float speed = 8.0f;
				if (env.window->isKeyDown(volt::Keys::LSHIFT)) {
					speed *= 2.5f;
				}
				velocity.z -= volt::maths::cosd(rot) * speed * delta;
				velocity.x += volt::maths::sind(rot) * speed * delta;
			}

			if (env.window->isKeyDown(volt::Keys::S)) {
				velocity.z += volt::maths::cosd(rot) * 4.0f * delta;
				velocity.x -= volt::maths::sind(rot) * 4.0f * delta;
			}

			if (env.window->isKeyDown(volt::Keys::A)) {
				velocity.z += volt::maths::cosd(rot + 90.0) * 7.0f * delta;
				velocity.x -= volt::maths::sind(rot + 90.0) * 7.0f * delta;
			}

			if (env.window->isKeyDown(volt::Keys::D)) {
				velocity.z -= volt::maths::cosd(rot + 90.0) * 7.0f * delta;
				velocity.x += volt::maths::sind(rot + 90.0) * 7.0f * delta;
			}

			if (env.window->isKeyDown(volt::Keys::SPACE)) {
				velocity.y += 20.0f * delta;
			}

			if (env.window->isKeyDown(volt::Keys::N)) {
				velocity.y -= 9.81f * delta;
			}

			velocity.y -= 10.0f * delta;



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


			volt::Vec3 t = _transform.position - last_sent;
			volt::Vec3 r = _transform.rotation - last_rot;

			if (abs(t.x) + abs(t.y) + abs(t.z) > 0.25f || abs(r.y) > 2.0f) {
				last_sent = _transform.position;
				last_rot = _transform.rotation;
				Json out;
				out.AddPair("action", "player_update");
				out.AddPair("position", Util::VectorToString(_transform.position));
				out.AddPair("rotation", Util::VectorToString(_transform.rotation));
				out.AddPair("token", env.token);
				out.AddPair("code", env.code);

				env.server->Send(out);
			}

			float yaw = _transform.rotation.y + 90.0f;
			float pitch = _transform.rotation.x;

			volt::Vec3 dir;
			dir.x = volt::maths::sind(yaw) * volt::maths::cosd(pitch);
			dir.y = volt::maths::sind(pitch);
			dir.z = -volt::maths::cosd(yaw) * volt::maths::cosd(pitch);


			GameObject temp;
			temp._hitbox = new Hitbox({ _transform.position.x, _transform.position.y + 7.5f, _transform.position.z }, { 0.1f,0.1f,0.1f });



			bool flag = false;
			GameObject* seen = nullptr;
			int count = 51;

			if (!flag) {
				for (auto [name, obj] : room->objects) {
					for (int i = 0; i < 12; i++) {
						temp._hitbox->position += dir;

						if (name.substr(0, 6) != "ground") {
							if (temp.CollidesWith(*obj, true)) {
								if (i < count) {
									count = i;
									seen = obj;
									break;
								}
							}
						}
						

					}

					temp._hitbox->position = { _transform.position.x, _transform.position.y + 7.5f, _transform.position.z };
				}

				if (seen) {
					seen->OnLook();
				}
			}
			

		}

		camera.setRotation(_transform.rotation);
		camera.setPosition({ _transform.position.x, _transform.position.y + 7.5f, _transform.position.z});

		env.window->setViewMatrix(camera);
	}
}