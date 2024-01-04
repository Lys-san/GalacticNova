#include "visualizer.h"

SDLWindowManager Visualizer::openWindow() {
 	SDLWindowManager windowManager(_width, _height, _name.c_str());
 	return windowManager;
}

Program Visualizer::initProgram(const FilePath &applicationPath) {
	Program program = loadProgram(
		applicationPath.dirPath() + "shaders/3D.vs.glsl",
		applicationPath.dirPath() + "shaders/tex3D.fs.glsl"
		);
	program.use();
	return program;
}


bool Visualizer::initGlew() {
	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << "Error at GLEW loading: "
		<< glewGetErrorString(glewInitError)
		<< std::endl;
		return false;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
	return true;
}


void Visualizer::loadTextureImages(const FilePath &filePath) {
	// using dirIterator = std::filesystem::recursive_directory_iterator;
	// std::string path = filePath.dirPath() + "../../assets/textures/";

	// for(const auto& dirEntry : dirIterator(path)) {
	// 	_textureImages.emplace_back(loadImage(dirEntry.path().string()));
	// 	std::cout << "Loaded " << dirEntry << std::endl;
	// }
}

uint Visualizer::width() const {
	return _width;
}

uint Visualizer::height() const {
	return _height;
}

////////////////////////////////////////////////////////////////////////////////


