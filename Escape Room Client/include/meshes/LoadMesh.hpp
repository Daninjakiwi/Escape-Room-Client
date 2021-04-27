#pragma once

#include <Volt.hpp>

namespace Meshes {
	volt::Mesh Load(const std::string& file_path);
	std::vector<volt::Mesh> LoadSeperate(const std::string& file_path);
}
