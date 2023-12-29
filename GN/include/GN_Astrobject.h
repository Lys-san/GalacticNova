/**
 * Author        : Lysandre M. (lysandre.macke@edu.univ-eiffel.fr)
 * Created       : 12-29-2023
 * Last modified : 12-29-2023 */

#ifndef GN_ASTRO_H
#define GN_ASTRO_H

#define GLIMAC_GL_CHECK_WARNING

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>

using namespace glimac;

class GN_Astrobject {
public:
	GN_Astrobject(std::string name,
		uint aphelion, 
		uint perihelion,
		unsigned double orbitalPeriod,
		unsigned double lengthOfDays,
		double orbitalInclination,
		FilePath texturePath
		) :
	_aphelion(aphelion),
	_perihelion(perihelion),
	_orbitalPeriod(orbitalPeriod),
	_lengthOfDays(lengthOfDays),
	_orbitalInclination(orbitalInclination),
	_texturePath(texturePath) {}

	~GN_Astrobject() {];

	/** Accessor for private attribute _texturePath. */
	FilePath texturePath() const;


private:
	uint            _aphelion;
	uint            _perihelion;
	unsigned double _orbitalPeriod;
	unsigned double _lengthOfDays;
	double          _orbitalInclination;
	FilePath        _texturePath;
};

#endif // GN_ASTRO_H