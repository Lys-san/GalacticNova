/**
 * Authors        : Lysandre M. (lysandre.macke@edu.univ-eiffel.fr) and Lori F. (lori.foulon@edu.univ-eiffel.fr)
 * Created       : 12-29-2023
 * Last modified : 01-06-2024 */

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

const GLfloat SUN_DIAMETER = 1400000.f;

class GN_Astrobject {
public:

	GN_Astrobject(const FilePath& applicationPath,
		std::string name,
		GLfloat     diameter,
		GN_Point    barycenter,
		GLfloat     aphelion, // Semi-major axis for satellite
		GLfloat     perihelion, // excentricity for satellite
		double      orbitalPeriod,
		double      lengthOfDays,
		double      orbitalInclination,
		FilePath    texturePath,
		GLuint      textureIndex,
		bool isSatellite
		) :
	_program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")),
	_name (name),
	_diameter (diameter),
	_barycenter(barycenter),
	_aphelion(aphelion),
	_perihelion(perihelion),
	_orbitalPeriod(orbitalPeriod),
	_lengthOfDays(lengthOfDays),
	_orbitalInclination(orbitalInclination),
	_mapImage(loadImage(texturePath)),
	_textureIndex(textureIndex),
	_isSatellite(isSatellite) {
		// load matrix refs
	    GLIMAC_CHECK_GLINT(_uMVPMatrixRef    = glGetUniformLocation(_program.getGLId(), "uMVPMatrix"));
		GLIMAC_CHECK_GLINT(_uMVMatrixRef     = glGetUniformLocation(_program.getGLId(), "uMVMatrix")); // Unused
		GLIMAC_CHECK_GLINT(_uNormalMatrixRef = glGetUniformLocation(_program.getGLId(), "uNormalMatrix")); // Unused
		GLIMAC_CHECK_GLINT(_uTextureRef      = glGetUniformLocation(_program.getGLId(), "uTexture"));

		glActiveTexture(GL_TEXTURE0);

		// init spheres
	}

	~GN_Astrobject() {};

	/** render object (use associated program) */
	void render();

	void setMatrices(const glm::mat4& MVMatrix, const glm::mat4& ProjMatrix);

	/** Bind to textures array at astrobject's texture index */
	void bindTexture(GLuint *textures);

	/** Get current Astrobject coordinate (center of sphere) */
	GN_Point getCurrentCoordinates();

	glm::mat4 display(const glm::mat4 &globalMVMatrix, const float refDiameter, const glm::mat4 &ProjMatrix, float time, const GLuint *textures, const GLsizei sphere_nb_vertices, int deplacement);

	/** updates MVMatrix and return it */
	glm::mat4 updatePosition(const glm::mat4 &refMVMatrix, const float refDiameter, const glm::mat4 &ProjMatrix, float time, int deplacement);

	void activeTexture();

	void loadShaders();

	/** Initializes at position*/
	void init();

	/** Accessor for private attribute _texturePath. */
	std::unique_ptr<Image> mapImage() const;

	GLuint textureIndex() const;

	GLfloat getDiameter() const;

private:
	static std::unique_ptr<Image> _loadImage(const FilePath &filepath);

	// base attributes
	Program                _program;
	std::string            _name;
	GLfloat                _diameter;
	GN_Point               _barycenter;
	GLfloat                _aphelion;
	GLfloat                _perihelion;
	double                 _orbitalPeriod;
	double                 _lengthOfDays;
	double                 _orbitalInclination;
	std::unique_ptr<Image> _mapImage;
	bool                   _isSatellite;

	// rendering
	// Sphere       _body;
	// ShapeVertex _vertices;
	// GLsizei      _nbVertices;

	GLint _uMVPMatrixRef;
	GLint _uMVMatrixRef;
	GLint _uNormalMatrixRef;
	GLint _uTextureRef;

	const GLuint _textureIndex;

};

#endif // GN_ASTRO_H