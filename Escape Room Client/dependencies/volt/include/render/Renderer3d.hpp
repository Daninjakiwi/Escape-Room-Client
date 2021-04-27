#pragma once
#include <util/maths/Matrix.hpp>
#include <render/Mesh.hpp>
#include <render/Material.hpp>
#include <render/Camera.hpp>
#include <render/Light.hpp>

namespace volt {
	class Renderer3d {
	public:
		Renderer3d() {};
		virtual ~Renderer3d() {};

		virtual void setViewMatrix(Camera& cam) {};
		virtual void drawMesh(Mesh& mesh, Material& material, Mat4 transform, unsigned int flags) {};
		virtual void loadEnvironmentMap(float* data, iVec2 size) {};
		virtual void setLight(int index, Light& light) {};

		virtual void renderFrame() {};
	};
}
