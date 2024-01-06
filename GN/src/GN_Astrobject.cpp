#include "GN_Astrobject.h"

void GN_Astrobject::render() {
	_program.use();
	glUniform1i(_uTextureRef, 0);
}

void GN_Astrobject::setMatrices(const glm::mat4& MVMatrix, const glm::mat4& ProjMatrix) {
	glUniformMatrix4fv(_uMVPMatrixRef,    1u, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
	glUniformMatrix4fv(_uMVMatrixRef,     1u, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(_uNormalMatrixRef, 1u, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
}

glm::mat4 GN_Astrobject::updatePosition(const glm::mat4 &refMVMatrix, const float refDiameter, const glm::mat4 &ProjMatrix, float time, int deplacement) {
	glm::mat4 MVMatrix = refMVMatrix;

	float ratio = _diameter/refDiameter;

    if (!_isSatellite){
        ratio *= 10;
    }

	// rotation around the sun
	MVMatrix = glm::rotate(MVMatrix, (time)*(float)_orbitalPeriod/100000.f, glm::vec3(0, 1, 0));
	// translation

	// radius from current astrobject <--> other astrobject it's orbiting around 
	double radius = (_excentricity == 0) ? 0 : 1 - _excentricity*cos((360/_orbitalPeriod)*(time));
	radius *= 50;

	MVMatrix = glm::translate(MVMatrix, glm::vec3(radius, 0, 0));
	// scale
	MVMatrix = glm::scale(MVMatrix, glm::vec3(ratio, ratio, ratio));
	// self rotation
	MVMatrix = glm::rotate(MVMatrix, time, glm::vec3(0, 1, 0));

	setMatrices(MVMatrix, ProjMatrix);

    return MVMatrix;
}

glm::mat4 GN_Astrobject::display(const glm::mat4 &globalMVMatrix, const float refDiameter, const glm::mat4 &ProjMatrix, float time, const GLuint *textures, const GLsizei sphere_nb_vertices, int deplacement) {
    render();
    glm::mat4 MVMatrix = updatePosition(globalMVMatrix, refDiameter, ProjMatrix, time, deplacement);



    // Set textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[_textureIndex]); // Bind earth texture in TU 0

    // Draw vertices
    glDrawArrays(GL_TRIANGLES, 0, sphere_nb_vertices);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture from TU 0

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[99]); // Bind earth texture in TU 0


    if(_hasRings) {
    	for(uint i = 0; i < N_ASTEROIDS; i++) {
    		setMatrices(MVMatrix * _asterMatrices[i], ProjMatrix);
    		glDrawArrays(GL_TRIANGLES, 0, sphere_nb_vertices);
    	}
    }
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture from TU 0



    return MVMatrix;
}

void GN_Astrobject::generateAsteroidsMatrices() {
	_asterMatrices = new glm::mat4[N_ASTEROIDS];

	float radius = 1.5;
	float offset = 0.5f;
	for(uint i = 0; i < N_ASTEROIDS; i++) {
		glm::mat4 model = glm::mat4(1.f);
		float angle = (float)i / (float)N_ASTEROIDS * 360.0f;
	    float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
	    float x = sin(angle) * radius + displacement;
	    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
	    float y = displacement * 0.15f; // keep height of field smaller compared to width of x and z
	    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
	    float z = cos(angle) * radius + displacement;
	    model = glm::translate(model, glm::vec3(x, y, z));

	    // 2. scale: scale between 0.05 and 0.25f
	    float scale = (rand() % 10) / 1000.0f + 0.025;
	    model = glm::scale(model, glm::vec3(scale));

	    // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
	    float rotAngle = (rand() % 360);
	    model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

	    // 4. now add to list of matrices
	    _asterMatrices[i] = model;

	    _hasRings = true;
	}


}

void GN_Astrobject::bindTexture(GLuint *textures) {
	// Textures specification
	const GLenum min_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR...
	const GLenum mag_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[_textureIndex]); // Bind texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _mapImage->getWidth(), _mapImage->getHeight(), 0, GL_RGBA, GL_FLOAT, _mapImage->getPixels()); // Load texture image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
}

std::unique_ptr<Image> GN_Astrobject::_loadImage(const FilePath &filepath) {
	std::unique_ptr<Image> image = loadImage(filepath);

	if (nullptr == image) {
		throw std::runtime_error("Unable to load image from file " + std::string(filepath));
	}
	return image;
}

GLuint GN_Astrobject::textureIndex() const {
	return _textureIndex;
}

GLfloat GN_Astrobject::getDiameter() const {
    return _diameter;
}

bool GN_Astrobject::hasRings() const {
	return _hasRings;
}