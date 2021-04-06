#include <core/PolyTexture.hpp>

PolyTexture::PolyTexture(const std::string& file, Quality initial) : low(), medium(), high(), low_init(false), medium_init(false), high_init(false), path(file) {
	setQuality(initial);
}

void PolyTexture::setQuality(Quality quality) {
	if (quality == Quality::LOW) {
		current = &low;
		if (!low_init) {
			low.init(path, 16);
			low_init = true;
		}
	}

	if (quality == Quality::MEDIUM) {
		current = &medium;
		if (!medium_init) {
			medium.init(path , 8);
			medium_init = true;
		}
	}

	if (quality == Quality::HIGH) {
		current = &high;
		if (!high_init) {
			high.init(path);
			high_init = true;
		}
	}
}