#define GLIMAC_GL_CHECK_WARNING

#include "visualizer.h"
#include "GN_Astrobject.h"

using namespace glimac;

enum VertexAttribute : GLuint {
  VERTEX_ATTR_POSITION   = 0,  // Position attribute
  VERTEX_ATTR_NORMAL     = 1,  // Normal attribute
  VERTEX_ATTR_TEX_COORDS = 2   // Texture coordinates attribute
};

const uint NB_TEXTURES = 12;


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

  // Shaders loading, compilation and uniforms location
  // Program program = Visualizer::initProgram(applicationPath);

  // create our astrobjects
  GN_Astrobject sun(applicationPath,
                    "Sun",
                    700000.f,
                    GN_Point(0.f, 0.f, 0.f),
                    0.f,
                    0.f,
                    0,
                    0,
                    0,
                    applicationPath.dirPath() + "../../assets/textures/SunMap.jpg",
                    0
                    );



    GN_Astrobject mercury(applicationPath,
                "Mercury",
                2436.f, // making bigger for better view
                GN_Point(0.f, 0.f, 0.f),
                69.8f,
                46.f,
                88.f,
                0,
                0,
                applicationPath.dirPath() + "../../assets/textures/MercuryMap.jpg",
                1
                );

    GN_Astrobject venus(applicationPath,
            "Venus",
            6052.f, // making bigger for better view
            GN_Point(0.f, 0.f, 0.f),
            108.9f,
            107.5f,
            226.7f,
            0,
            0,
            applicationPath.dirPath() + "../../assets/textures/VenusMap.jpg",
            2
            );

    GN_Astrobject earth(applicationPath,
                    "Earth",
                    6378.f, // making bigger for better view
                    GN_Point(0.f, 0.f, 0.f),
                    152.1f,
                    147.1f,
                    365.2,
                    0,
                    0,
                    applicationPath.dirPath() + "../../assets/textures/EarthMap.jpg",
                    3
                    );

    GN_Astrobject mars(applicationPath,
            "Mars",
            3396.f, // making bigger for better view
            GN_Point(0.f, 0.f, 0.f),
            //249.3f,
            200.f,
            206.7f,
            365.2,
            0,
            0,
            applicationPath.dirPath() + "../../assets/textures/MarsMap.jpg",
            4
            );

    GN_Astrobject jupiter(applicationPath,
            "Jupiter",
            71492.f, // making bigger for better view
            GN_Point(0.f, 0.f, 0.f),
            //816.4f,
            250.f,
            740.6f,
            4331.f,
            0,
            0,
            applicationPath.dirPath() + "../../assets/textures/JupiterMap.jpg",
            5
            );

    GN_Astrobject saturn(applicationPath,
            "Saturn",
            60268.f, // making bigger for better view
            GN_Point(0.f, 0.f, 0.f),
            //1506.5f,
            300.f,
            1357.6f,
            10747.f,
            0,
            0,
            applicationPath.dirPath() + "../../assets/textures/SaturnMap.jpg",
            6
            );

    GN_Astrobject uranus(applicationPath,
            "Uranus",
            25559.f, // making bigger for better view
            GN_Point(0.f, 0.f, 0.f),
            //3001.4f,
            400.f,
            2732.7f,
            30689.f,
            0,
            0,
            applicationPath.dirPath() + "../../assets/textures/UranusMap.jpg",
            7
            );

    GN_Astrobject neptune(applicationPath,
        "Neptune",
        24764.f, // making bigger for better view
        GN_Point(0.f, 0.f, 0.f),
        //4558.9f,
        450.f,
        4471.1f,
        59800.f,
        0,
        0,
        applicationPath.dirPath() + "../../assets/textures/NeptuneMap.jpg",
        8
        );

    GN_Astrobject pluto(applicationPath,
        "Pluto",
        24764.f, // making bigger for better view
        GN_Point(0.f, 0.f, 0.f),
        //4558.9f,
        450.f,
        4471.1f,
        59800.f,
        0,
        0,
        applicationPath.dirPath() + "../../assets/textures/PlutoMap.jpg",
        9
        );

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


  // texture specification
  GLuint textures[NB_TEXTURES];
  glGenTextures(NB_TEXTURES, textures);

  sun.bindTexture(textures);
  earth.bindTexture(textures);
  mercury.bindTexture(textures);
  venus.bindTexture(textures);
  mars.bindTexture(textures);
  jupiter.bindTexture(textures);
  saturn.bindTexture(textures);
  neptune.bindTexture(textures);
  pluto.bindTexture(textures);

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
    glm::mat4 global_MVMatrix = camera.getViewMatrix();

    // === SUN ===
    sun.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, 0);

    // === Mercury ===
    mercury.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -12);

    // === VENUS === 
    venus.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -14);

    // === EARTH === 
    earth.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -16);

    // === MARS === 
    mars.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -18);

    // === Jupiter === 
    jupiter.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -20);

    // === Saturn === 
    saturn.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -22);

    // === Uranus ===
    uranus.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -24);
    
    // === Neptune ===
    neptune.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -26);
    
    // === Pluto ===
    pluto.display(global_MVMatrix, ProjMatrix, time, textures, sphere_nb_vertices, -28);

    glBindVertexArray(0); // Unbind vao (from active VAO)
    // Update the display
    windowManager.swapBuffers();
  }

  glDeleteTextures(NB_TEXTURES, textures); // Release texture

  std::cout << "Closing application" << std::endl;
  return EXIT_SUCCESS;
}
