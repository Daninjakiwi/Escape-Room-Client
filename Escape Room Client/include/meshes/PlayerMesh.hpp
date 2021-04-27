#pragma once
#include <Volt.hpp>

float ox = -0.5f;
float oz = 0.5f;

namespace Meshes {
	volt::Mesh PlayerMesh() {
		volt::Mesh mesh;
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(0.0f, 0.0f, 1.0f), volt::Vec2(0.0f, 1.0f));
												 
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f,-1.0f +oz), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f,-1.0f +oz), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 1.0f));
												   
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f, -1.0f+oz), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f, -1.0f+oz), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f, -1.0f+oz), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f, -1.0f+oz), volt::Vec3(0.0f, 0.0f, -1.0f), volt::Vec2(0.0f, 1.0f));
												  
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f,-1.0f +oz), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f,-1.0f +oz), volt::Vec3(-1.0f, 0.0f, 0.0f), volt::Vec2(0.0f, 1.0f));
												 
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f, 0.0f +oz), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 1.0f,-1.0f +oz), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 1.0f,-1.0f +oz), volt::Vec3(0.0f, 1.0f, 0.0f), volt::Vec2(0.0f, 1.0f));
												   
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(0.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f, 0.0f +oz), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(1.0f, 0.0f));
		mesh.vertices.emplace_back(volt::Vec3(0.0f +ox, 0.0f,-1.0f +oz), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(1.0f, 1.0f));
		mesh.vertices.emplace_back(volt::Vec3(1.0f +ox, 0.0f,-1.0f +oz), volt::Vec3(0.0f, -1.0f, 0.0f), volt::Vec2(0.0f, 1.0f));

		for (int i = 0; i < 6; i++) {
			int offset = i * 4;
			mesh.indices.push_back(0 + offset);
			mesh.indices.push_back(1 + offset);
			mesh.indices.push_back(2 + offset);
			mesh.indices.push_back(2 + offset);
			mesh.indices.push_back(3 + offset);
			mesh.indices.push_back(0 + offset);
		}

		return mesh;
	}
}
