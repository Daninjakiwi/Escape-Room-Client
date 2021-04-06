#pragma once
#include <vector>
#include <util/maths/Vector.hpp>

namespace volt {
	enum class PrimativeTypes {
		QUAD,CUBE,SPHERE
	};

	struct Vertex {
		Vec3 position;
		Vec3 normal;
		Vec2 uv;

		Vertex(Vec3 _pos, Vec3 _normal, Vec2 _uv);
	};

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		static Mesh createPrimative(PrimativeTypes type, Vec2 scale = { 1.0f,1.0f });
	};

	
}