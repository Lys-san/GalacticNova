/**
 * Author        : Lysandre M. (lysandre.macke@edu.univ-eiffel.fr)
 * Created       : 12-29-2023
 * Last modified : 12-29-2023 */

#ifndef VISU_H
#define VISU_H

#define GLIMAC_GL_CHECK_WARNING

#include <GL/glew.h>
#include <algorithm>
#include <array>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <iostream>
#include <memory>
#include <tuple>

// #include <filesystem>

using namespace glimac;


/** Visualizer */
class Visualizer {
public:
	Visualizer()                                          : _width(800u),  _height(600u),   _name("GN_Visualizer") { };
	Visualizer(uint width, uint height)                   : _width(width), _height(height), _name("GN_Visualizer") { };
	Visualizer(uint width, uint height, std::string name) : _width(width), _height(height), _name(name)            { };

	~Visualizer() {};

	/** Open window for current visualizer. */
	SDLWindowManager openWindow();

	/** Shaders loading and compilation */
	static Program initProgram(const FilePath &applicationPath);

	/** initializes glew for OpenGL3+ support*/
	static bool initGlew();

	/** Loads and stores images contained in the assets/texture folder. */
	void loadTextureImages(const FilePath &filepath);

	/** Accessor for private field _width. */
	uint width() const;

	/** Accessor for private field _height. */
	uint height() const;

private:
	static std::unique_ptr<Image> loadImage(const FilePath &filepath);

	// private attributes
	const std::string _name;

	// window dimensions
	const uint _width;
	const uint _height;

	// texture images vector
	std::vector<std::unique_ptr<Image>> _textureImages;
};

#endif // VISU_H