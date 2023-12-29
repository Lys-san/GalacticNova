#include "visualizer.h"

void Visualizer::initGlew() {

}

void Visualizer::loadTextureImages(const FilePath &filePath) {
	using dirIterator = std::filesystem::recursive_directory_iterator;
	auto path = filePath.dirPath() + "../../assets/textures/";

	for(const auto& dirEntry : dirIterator(path)) {
		_textureImages.emplace_back(loadImage(dirEntry));
		std::cout << "Loaded " << dirEntry << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////

static void std::unique_ptr<Image> Visualizer::loadImage(const FilePath &filepath) {
	std::unique_ptr<Image> image = loadImage(filepath);

	if (nullptr == image) {
		throw std::runtime_error("Unable to load image from file " + std::string(filepath));
	}

	return image;
}
