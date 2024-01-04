#include "GN_Astrobject.h"

std::unique_ptr<Image> GN_Astrobject::_loadImage(const FilePath &filepath) {
	std::unique_ptr<Image> image = loadImage(filepath);

	if (nullptr == image) {
		throw std::runtime_error("Unable to load image from file " + std::string(filepath));
	}
	return image;
}