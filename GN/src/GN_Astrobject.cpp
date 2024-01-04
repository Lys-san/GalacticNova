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

void GN_Astrobject::bindTexture() {
	// Textures specification
	const GLenum min_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR...
	const GLenum mag_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_EARTH_MAP]); // Bind texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mapImage->getWidth(), mapImage->getHeight(), 0, GL_RGBA, GL_FLOAT, mapImage->getPixels()); // Load texture image
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

