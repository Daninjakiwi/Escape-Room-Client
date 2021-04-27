#pragma once
#include "objects/ChessBoard.hpp"

ChessBoard::ChessBoard() : GameObject() {
	_material = new volt::PbrMaterial("resources/textures/pbr/chess_board");

	_mesh = new volt::Mesh();
	//FRONT
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, 0.0f), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, 0.0f), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.5f, 0.015625f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, 0.0f), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.0f, 0.015625f));

	//RIGHT
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, -1.0f), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, -1.0f), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.5f, 0.015625f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, 0.0f), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.015625f));

	//BACK
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, -1.0f), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, -1.0f), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.5f, 0.015625f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, -1.0f), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.0f, 0.015625f));

	//LEFT
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, 0.0f), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, 0.0f), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.5f, 0.015625f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, -1.0f), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.015625f));

	//TOP
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, 0.0f), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, 0.0f), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.05f, -1.0f), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.5f, 1.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.05f, -1.0f), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.0f, 1.0f));

	//BOTTTOM
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(0.5f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, 0.0f), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(1.0f, 0.0f));
	_mesh->vertices.emplace_back(volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(1.0f, 1.0f));
	_mesh->vertices.emplace_back(volt::Vec3(1.0f, 0.0f, -1.0f), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(0.5f, 1.0f));

	for (int i = 0; i < 6; i++) {
		int offset = i * 4;
		_mesh->indices.push_back(0 + offset);
		_mesh->indices.push_back(1 + offset);
		_mesh->indices.push_back(2 + offset);
		_mesh->indices.push_back(2 + offset);
		_mesh->indices.push_back(3 + offset);
		_mesh->indices.push_back(0 + offset);
	}
}

ChessBoard::~ChessBoard() {
	delete _mesh;
	delete _material;
}