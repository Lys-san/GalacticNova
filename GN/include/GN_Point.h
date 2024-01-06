/**
 * Author        : Lysandre M. (lysandre.macke@edu.univ-eiffel.fr) and Lori F. (lori.foulon@edu.univ-eiffel.fr)
 * Created       : 01-04-2024
 * Last modified : 01-04-2024 */


#ifndef GN_POINT_H
#define GN_POINT_H

#define GLIMAC_GL_CHECK_WARNING


class GN_Point {
public:
	GN_Point(GLfloat x, GLfloat y, GLfloat z) : _x(x), _y(y), _z(z) {};

	~GN_Point() {};

private:
	GLfloat _x;
	GLfloat _y;
	GLfloat _z;
};
#endif