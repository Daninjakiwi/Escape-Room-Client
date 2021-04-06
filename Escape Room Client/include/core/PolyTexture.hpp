#pragma once
#include <string>
#include <Volt.hpp>

enum class Quality {
	LOW = 0,MEDIUM = 1, HIGH = 2
};

class PolyTexture {
private:
	volt::Texture* current;
	volt::Texture low;
	volt::Texture medium;
	volt::Texture high;
	bool low_init;
	bool medium_init;
	bool high_init;
	std::string path;
public:
	PolyTexture(const std::string& file, Quality initial = Quality::LOW);

	void setQuality(Quality quality);

	operator volt::Texture& () const { return *current; };
};
