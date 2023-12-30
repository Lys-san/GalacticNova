#define GLIMAC_GL_CHECK_WARNING

#include "visualizer.h"

using namespace glimac;



enum VertexAttribute : GLuint {
  VERTEX_ATTR_POSITION   = 0,  // Position attribute
  VERTEX_ATTR_NORMAL     = 1,  // Normal attribute
  VERTEX_ATTR_TEX_COORDS = 2   // Texture coordinates attribute
};

enum TextureIdx {
  TEX_EARTH_MAP,
  TEX_CLOUD_MAP,
  TEX_MOON_MAP,

  NB_TEXTURES
};

static void _updateMatrices(
  const glm::mat4& MVMatrix,
  const glm::mat4& ProjMatrix,
  const GLint uMVPMatrix_ref,
  const GLint uMVMatrix_ref,
  const GLint uNormalMatrix_ref
)
{
  glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  glm::mat4 MVPMatrix    = ProjMatrix * MVMatrix;

  // Set uniforms
  glUniformMatrix4fv(uMVPMatrix_ref,    1u, GL_FALSE, glm::value_ptr(MVPMatrix));
  glUniformMatrix4fv(uMVMatrix_ref,     1u, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(uNormalMatrix_ref, 1u, GL_FALSE, glm::value_ptr(NormalMatrix));
}

struct EarthProgram {
  Program m_program;

  GLint m_uMVPMatrix_ref;
  GLint m_uMVMatrix_ref;
  GLint m_uNormalMatrix_ref;
  GLint m_uEarthTexture_ref;
  GLint m_uCloudTexture_ref;

  EarthProgram(const FilePath& app_path)
    : m_program { loadProgram(app_path.dirPath() + "shaders/3D.vs.glsl",
                              app_path.dirPath() + "shaders/multiTex3D.fs.glsl")}
  {
    GLIMAC_CHECK_GLINT(m_uMVPMatrix_ref    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix"));
    GLIMAC_CHECK_GLINT(m_uMVMatrix_ref     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix")); // Unused
    GLIMAC_CHECK_GLINT(m_uNormalMatrix_ref = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix")); // Unused
    GLIMAC_CHECK_GLINT(m_uEarthTexture_ref = glGetUniformLocation(m_program.getGLId(), "uEarthTexture"));
    GLIMAC_CHECK_GLINT(m_uCloudTexture_ref = glGetUniformLocation(m_program.getGLId(), "uCloudTexture"));
  }

  void use()
  {
    m_program.use();
    glUniform1i(m_uEarthTexture_ref, 0); // Earth texture is binded to Texture Unit 0
    glUniform1i(m_uCloudTexture_ref, 1); // Earth texture is binded to Texture Unit 1
  }

  void setMatrices(const glm::mat4& earth_MVMatrix, const glm::mat4& ProjMatrix)
  {
    glUniformMatrix4fv(m_uMVPMatrix_ref,    1u, GL_FALSE, glm::value_ptr(ProjMatrix * earth_MVMatrix));
    glUniformMatrix4fv(m_uMVMatrix_ref,     1u, GL_FALSE, glm::value_ptr(earth_MVMatrix));
    glUniformMatrix4fv(m_uNormalMatrix_ref, 1u, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earth_MVMatrix))));
  }
};

struct MoonProgram {
  Program m_program;

  GLint m_uMVPMatrix_ref;
  GLint m_uMVMatrix_ref;
  GLint m_uNormalMatrix_ref;
  GLint m_uTexture_ref;

  MoonProgram(const FilePath& app_path)
    : m_program { loadProgram(app_path.dirPath() + "shaders/3D.vs.glsl",
                              app_path.dirPath() + "shaders/tex3D.fs.glsl")}
  {
    GLIMAC_CHECK_GLINT(m_uMVPMatrix_ref    = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix"));
    GLIMAC_CHECK_GLINT(m_uMVMatrix_ref     = glGetUniformLocation(m_program.getGLId(), "uMVMatrix")); // Unused
    GLIMAC_CHECK_GLINT(m_uNormalMatrix_ref = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix")); // Unused
    GLIMAC_CHECK_GLINT(m_uTexture_ref      = glGetUniformLocation(m_program.getGLId(), "uTexture"));
  }

  void use()
  {
    m_program.use();
    glUniform1i(m_uTexture_ref, 0); // Moon texture is binded to Texture Unit 0
  }

  void setMatrices(const glm::mat4& moon_MVMatrix, const glm::mat4& ProjMatrix)
  {
    glUniformMatrix4fv(m_uMVPMatrix_ref,    1u, GL_FALSE, glm::value_ptr(ProjMatrix * moon_MVMatrix));
    glUniformMatrix4fv(m_uMVMatrix_ref,     1u, GL_FALSE, glm::value_ptr(moon_MVMatrix));
    glUniformMatrix4fv(m_uNormalMatrix_ref, 1u, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(moon_MVMatrix))));
  }
};

static std::unique_ptr<Image> _loadImage(
  const FilePath& filepath
)
{
  std::unique_ptr<Image> image = loadImage(filepath);
  if (nullptr == image) {
    throw std::runtime_error("Unable to load image (from file " + std::string(filepath) + ")");
  }
  return image;
}

int main(int argc, char** argv) {
  Visualizer visualizer;
  auto windowManager = visualizer.openWindow();

  uint window_width = visualizer.width();
  uint window_height = visualizer.height();
  float window_ar = (float) visualizer.width() / visualizer.height();

  if (!Visualizer::initGlew()) {
    return EXIT_FAILURE;
  }

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  FilePath applicationPath(argv[0]);

  // Textures loading
  std::unique_ptr<Image> earth_map_img = _loadImage(
    applicationPath.dirPath() + "../../assets/textures/EarthMap.jpg"
  );
  std::unique_ptr<Image> cloud_map_img = _loadImage(
    applicationPath.dirPath() + "../../assets/textures/CloudMap.jpg"
  );
  std::unique_ptr<Image> moon_map_img  = _loadImage(
    applicationPath.dirPath() + "../../assets/textures/MoonMap.jpg"
  );

  // Shaders loading, compilation and uniforms location
  Program program = Visualizer::initProgram(applicationPath);

  EarthProgram earth_program(applicationPath);
  MoonProgram moon_program(applicationPath);

  // Init rendering and camera
  glEnable(GL_DEPTH_TEST); // Enable Depth test
  glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), window_ar, 0.1f, 100.f); 
  FreeflyCamera camera;

  // Init vertices
  // Sphere
  const GLfloat sphere_radius = 1.f;
  Sphere sphere(sphere_radius, 32u, 32u);
  const ShapeVertex *sphere_vertices = sphere.getDataPointer();
  const GLsizei sphere_nb_vertices   = sphere.getVertexCount();

  // Moons
  const uint nb_moons = 32u;
  std::array<std::tuple<glm::vec3,glm::vec3,float>, nb_moons> moon_prop;
  std::generate(
    moon_prop.begin(), moon_prop.end(),
    [sphere_radius]() {
      float offset = glm::linearRand(0.f, 360.f);
      return std::make_tuple(glm::sphericalRand(1.f), glm::sphericalRand(sphere_radius), offset);
    }
  );

  // Vertex specification
  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind VBO

  const GLsizei vertices_stride              = sizeof(ShapeVertex);
  const GLvoid* vertices_attr_position_off   = reinterpret_cast<GLvoid*>(offsetof(ShapeVertex, position));
  const GLvoid* vertices_attr_normal_off     = reinterpret_cast<GLvoid*>(offsetof(ShapeVertex, normal));
  const GLvoid* vertices_attr_tex_coords_off = reinterpret_cast<GLvoid*>(offsetof(ShapeVertex, texCoords));

  glBufferData(GL_ARRAY_BUFFER, sphere_nb_vertices * vertices_stride, sphere_vertices, GL_STATIC_DRAW); // Copy data to VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao); // Bind the VAO

  glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind VBO

  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, vertices_stride, vertices_attr_position_off);

  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, vertices_stride, vertices_attr_normal_off);

  glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);
  glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, vertices_stride, vertices_attr_tex_coords_off);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
  glBindVertexArray(0); // Unbind VAO

  // Textures specification
  const GLenum min_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR...
  const GLenum mag_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR

  GLuint textures_vtex[NB_TEXTURES];
  glGenTextures(NB_TEXTURES, textures_vtex);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_EARTH_MAP]); // Bind texture object
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, earth_map_img->getWidth(), earth_map_img->getHeight(), 0, GL_RGBA, GL_FLOAT, earth_map_img->getPixels()); // Load texture image
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_CLOUD_MAP]); // Bind texture object
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cloud_map_img->getWidth(), cloud_map_img->getHeight(), 0, GL_RGBA, GL_FLOAT, cloud_map_img->getPixels()); // Load texture image
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_MOON_MAP]); // Bind texture object
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, moon_map_img->getWidth(), moon_map_img->getHeight(), 0, GL_RGBA, GL_FLOAT, moon_map_img->getPixels()); // Load texture image
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

  // Application loop:
  const float pan_motio_speed = 1.f;
  const float left_right_motion_speed = 100.f;

  bool done = false;
  while (!done) {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e)) {
      switch (e.type) {
      case SDL_KEYDOWN: 
        switch (e.key.keysym.sym) {
        case SDLK_f:
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          break;
        case SDLK_l:
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          break;
        case SDLK_z:
          camera.moveFront(-pan_motio_speed);
          break;
        case SDLK_q:
          camera.moveLeft(-pan_motio_speed);
          break;
        case SDLK_s:
          camera.moveFront(pan_motio_speed);
          break;
        case SDLK_d:
          camera.moveLeft(pan_motio_speed);
          break;
        case SDLK_ESCAPE:
          done = true; // Leave the loop after this iteration
          break;
        }
        break;
      
      case SDL_MOUSEMOTION:
        if (e.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
          camera.rotateLeft((float) e.motion.xrel / window_width  * left_right_motion_speed);
          camera.rotateUp  ((float) e.motion.yrel / window_height * left_right_motion_speed);
        }
        break;

      case SDL_QUIT:
        done = true; // Leave the loop after this iteration
      }
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    // Rendering code:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear rendering buffer

    glBindVertexArray(vao); // Bind vao as active VAO
    float time = windowManager.getTime();

    // Compute global matrices
    // glm::mat4 global_MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
    glm::mat4 global_MVMatrix = camera.getViewMatrix();

    // Enable eath program and set transformation matrices
    earth_program.use();
    earth_program.setMatrices(glm::rotate(global_MVMatrix, time, glm::vec3(0, 1, 0)), ProjMatrix);

    // Set earth textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_EARTH_MAP]); // Bind earth texture in TU 0
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_CLOUD_MAP]); // Bind cloud texture in TU 1

    // Draw earth vertices
    glDrawArrays(GL_TRIANGLES, 0, sphere_nb_vertices);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind cloud texture from TU 1

    // Draw moons
    moon_program.use();

    // Set moon texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures_vtex[TEX_MOON_MAP]); // Bind moon texture in TU 0

    for (const std::tuple<glm::vec3,glm::vec3,float>& angle_offset: moon_prop) {
      const glm::vec3& init_angle = std::get<0>(angle_offset);
      const glm::vec3& rot_angle  = std::get<1>(angle_offset);
      const float offset          = std::get<2>(angle_offset);

      glm::mat4 moon_MVMatrix = global_MVMatrix;
      moon_MVMatrix = glm::rotate   (moon_MVMatrix, offset, init_angle);
      moon_MVMatrix = glm::rotate   (moon_MVMatrix,   time,  rot_angle);
      moon_MVMatrix = glm::translate(moon_MVMatrix, glm::vec3(-2, 0, 0));
      moon_MVMatrix = glm::scale    (moon_MVMatrix, glm::vec3(0.2, 0.2, 0.2));
      moon_program.setMatrices(moon_MVMatrix, ProjMatrix);

      glDrawArrays(GL_TRIANGLES, 0, sphere_nb_vertices);
    }

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind moon texture from TU 0
    glBindVertexArray(0); // Unbind vao (from active VAO)

    // Update the display
    windowManager.swapBuffers();
  }

  glDeleteTextures(NB_TEXTURES, textures_vtex); // Release texture

  std::cout << "Closing application" << std::endl;
  return EXIT_SUCCESS;
}
