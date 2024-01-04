/**
 * Author        : Lysandre M. (lysandre.macke@edu.univ-eiffel.fr)
 * Created       : 12-29-2023
 * Last modified : 01-04-2024 */

#ifndef GN_ASTRO_H
#define GN_ASTRO_H

#define GLIMAC_GL_CHECK_WARNING

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <memory>
#include "GN_Point.h"
#include <iostream>


using namespace glimac;

class GN_Astrobject {
public:

	GN_Astrobject(const FilePath& applicationPath,
		std::string name,
		GLfloat radius,
		GN_Point barycenter,
		uint aphelion, 
		uint perihelion,
		double orbitalPeriod,
		double lengthOfDays,
		double orbitalInclination,
		FilePath texturePath
		) :
	_program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")),
	_radius (radius),
	_barycenter(barycenter),
	_aphelion(aphelion),
	_perihelion(perihelion),
	_orbitalPeriod(orbitalPeriod),
	_lengthOfDays(lengthOfDays),
	_orbitalInclination(orbitalInclination),
	_mapImage(loadImage(texturePath)) {
		std::cout << "here" << std::endl;
	    GLIMAC_CHECK_GLINT(_uMVPMatrixRef    = glGetUniformLocation(_program.getGLId(), "uMVPMatrix"));
		GLIMAC_CHECK_GLINT(_uMVMatrixRef     = glGetUniformLocation(_program.getGLId(), "uMVMatrix")); // Unused
		GLIMAC_CHECK_GLINT(_uNormalMatrixRef = glGetUniformLocation(_program.getGLId(), "uNormalMatrix")); // Unused
		GLIMAC_CHECK_GLINT(_uTextureRef      = glGetUniformLocation(_program.getGLId(), "uTexture"));
	}

	~GN_Astrobject() {};



	void loadShaders();

	/** Initializes at position*/
	void init();

	/** Accessor for private attribute _texturePath. */
	std::unique_ptr<Image> mapImage() const;


private:
		static std::unique_ptr<Image> _loadImage(const FilePath &filepath);

	


	// base attributes
	Program                _program;
	GLfloat                _radius;
	GN_Point               _barycenter;
	uint                   _aphelion;
	uint                   _perihelion;
	double                 _orbitalPeriod;
	double                 _lengthOfDays;
	double                 _orbitalInclination;
	std::unique_ptr<Image> _mapImage;

	// rendering
	// const Sphere       _body;
	// const ShapeVertex _vertices;
	// const GLsizei      _nbVertices;

	GLint _uMVPMatrixRef;
	GLint _uMVMatrixRef;
	GLint _uNormalMatrixRef;
	GLint _uTextureRef;

};

#endif // GN_ASTRO_H