#pragma once
#include "meshes/obj_loader.h"
#include "meshes/LoadMesh.hpp"

namespace Meshes {

	volt::Mesh Load(const std::string& file_path) {
		volt::Mesh mesh;

		objl::Loader loader;

		loader.LoadFile(file_path); 

		for (auto it = loader.LoadedVertices.begin(); it < loader.LoadedVertices.end(); it++) {
			mesh.vertices.emplace_back(volt::Vec3(it->Position.X, it->Position.Y, it->Position.Z), volt::Vec3(it->Normal.X, it->Normal.Y, it->Normal.Z), volt::Vec2(it->TextureCoordinate.X, it->TextureCoordinate.Y));
			//std::cout << volt::Vec3(it->Position.X, it->Position.Y, it->Position.Z) << std::endl;
		}


		for (auto it = loader.LoadedIndices.begin(); it < loader.LoadedIndices.end(); it++) {
			mesh.indices.push_back(*it);
		}

		return mesh;
	}

	std::vector<volt::Mesh> LoadSeperate(const std::string& file_path) {
		std::vector<volt::Mesh> out;
		objl::Loader loader;


		loader.LoadFile(file_path);


		for (auto i = loader.LoadedMeshes.begin(); i < loader.LoadedMeshes.end(); i++) {
			//std::cout << it->Indices.size() << std::endl;
			out.push_back({});
			for (auto it = i->Vertices.begin();it < i->Vertices.end(); it++) {
				out[out.size() - 1].vertices.emplace_back(volt::Vec3(it->Position.X, it->Position.Y, it->Position.Z), volt::Vec3(it->Normal.X, it->Normal.Y, it->Normal.Z), volt::Vec2(it->TextureCoordinate.X, it->TextureCoordinate.Y));
			}

			for (auto it = i->Indices.begin(); it < i->Indices.end(); it++) {
				out[out.size() - 1].indices.push_back(*it);
			}
		}

		return out;

	}
}
