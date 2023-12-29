#pragma once

#include <GL/glew.h>
#include "glm.hpp"

#if defined(GLIMAC_GL_CHECK_WARNING)
#  define GLIMAC_CHECK_GLINT(call)                                 \
  do {                                                             \
    GLint ret = (call);                                            \
    if (ret < 0) {                                                 \
      fprintf(                                                     \
        stderr, "%s:%d Warning: Negative value returned.\n",       \
        __FILE__, __LINE__                                         \
      );                                                           \
    }                                                              \
  } while (0)

#else
#  define GLIMAC_CHECK_GLINT(call)                                 \
  do {                                                             \
    GLint ret = (call);                                            \
    if (ret < 0) {                                                 \
      fprintf(                                                     \
        stderr, "%s:%d Error: Negative value returned.\n",         \
        __FILE__, __LINE__                                         \
      );                                                           \
      exit(EXIT_FAILURE);                                          \
    }                                                              \
  } while (0)
#endif

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

}
