#define GLIMAC_GL_CHECK_WARNING

#include "visualizer.h"
#include "GN_Astrobject.h"

using namespace glimac;

enum VertexAttribute : GLuint {
  VERTEX_ATTR_POSITION   = 0,  // Position attribute
  VERTEX_ATTR_NORMAL     = 1,  // Normal attribute
  VERTEX_ATTR_TEX_COORDS = 2   // Texture coordinates attribute
};

const uint NB_TEXTURES = 100;

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


  std::unique_ptr<Image> asterMapImage  = GN_Astrobject::_loadImage(
    applicationPath.dirPath() + "../../assets/textures/rock.png"
  );

  // create our astrobjects
    GN_Astrobject sun(applicationPath,
        "Sun",
        1400000.f,
        GN_Point(0.f, 0.f, 0.f),
        0.f,
        0.f,
        0.f,
        0,
        600.f,
        0,
        applicationPath.dirPath() + "../../assets/textures/SunMap.jpg",
        0,
        false
        );

    GN_Astrobject mercury(applicationPath,
        "Mercury",
        4879.f,
        GN_Point(0.f, 0.f, 0.f),
        69.8f,
        46.f,
        0.206f,
        88.f,
        4222.6,
        7.,
        applicationPath.dirPath() + "../../assets/textures/MercuryMap.jpg",
        1,
        false
        );

    GN_Astrobject venus(applicationPath,
        "Venus",
        12104.f,
        GN_Point(0.f, 0.f, 0.f),
        108.9f,
        107.5f,
        0.0068f,
        226.7f,
        2802.,
        3.4,
        applicationPath.dirPath() + "../../assets/textures/VenusMap.jpg",
        2,
        false
        );

    GN_Astrobject earth(applicationPath,
        "Earth",
        12756.f,
        GN_Point(0.f, 0.f, 0.f),
        152.1f,
        147.1f,
        0.0167,
        365.2,
        24.,
        0.,
        applicationPath.dirPath() + "../../assets/textures/EarthMap.jpg",
        3,
        false
        );

    GN_Astrobject mars(applicationPath,
        "Mars",
        6792.f,
        GN_Point(0.f, 0.f, 0.f),
        249.3f,
        206.7f,
        0.0934f,
        687.0,
        24.7,
        1.8,
        applicationPath.dirPath() + "../../assets/textures/MarsMap.jpg",
        4,
        false
        );

    GN_Astrobject jupiter(applicationPath,
        "Jupiter",
        142984.f,
        GN_Point(0.f, 0.f, 0.f),
        816.4f,
        740.6f,
        0.0485f,
        4331.f,
        9.9,
        1.3,
        applicationPath.dirPath() + "../../assets/textures/JupiterMap.jpg",
        5,
        false
        );

    GN_Astrobject saturn(applicationPath,
        "Saturn",
        120536.f,
        GN_Point(0.f, 0.f, 0.f),
        1506.5f,
        1357.6f,
        0.0556f,
        10747.f,
        10.7,
        2.5,
        applicationPath.dirPath() + "../../assets/textures/SaturnMap.jpg",
        6,
        false
        );

    GN_Astrobject uranus(applicationPath,
        "Uranus",
        51118.f,
        GN_Point(0.f, 0.f, 0.f),
        3001.4f,
        2732.7f,
        0.0472f,
        30689.f,
        17.2,
        0.8,
        applicationPath.dirPath() + "../../assets/textures/UranusMap.jpg",
        7,
        false
        );

    GN_Astrobject neptune(applicationPath,
        "Neptune",
        49528.f,
        GN_Point(0.f, 0.f, 0.f),
        4558.9f,
        4471.1f,
        0.0086f,
        59800.f,
        16.1,
        1.8,
        applicationPath.dirPath() + "../../assets/textures/NeptuneMap.jpg",
        8,
        false
        );

    GN_Astrobject pluto(applicationPath,
        "Pluto",
        2376.f, // full diameter
        GN_Point(0.f, 0.f, 0.f),
        7375.9f,
        4436.8f,
        0.25f,
        90560.f,
        153.3,
        17.2,
        applicationPath.dirPath() + "../../assets/textures/PlutoMap.jpg",
        9,
        false
        );

    GN_Astrobject moon(applicationPath,
        "Moon",
        3475.f,
        GN_Point(0.f, 0.f, 0.f),
        //384400.f,
        1.5f,
        1.5f, // Just for debugMode
        0.0549f,
        0.,
        0.,
        5.145,
        applicationPath.dirPath() + "../../assets/textures/MoonMap.jpg",
        10,
        true
        );

    GN_Astrobject phobos(applicationPath,
        "Phobos",
        1348.62f, // can't find the radius or diameter
        GN_Point(0.f, 0.f, 0.f),
        1.5f,
        1.5f, // Just for debugMode
        0.0151f,
        0.,
        0.,
        1.08,
        applicationPath.dirPath() + "../../assets/textures/PhobosMap.jpg",
        11,
        true
        );

    GN_Astrobject deimos(applicationPath,
        "Deimos",
        425.88f,
        GN_Point(0.f, 0.f, 0.f),
        2.5f,
        2.5f, // Just for debugMode
        0.0005f,
        0.,
        0.,
        1.79,
        applicationPath.dirPath() + "../../assets/textures/DeimosMap.jpg",
        12,
        true
        );

    GN_Astrobject callisto(applicationPath,
        "Callisto",
        4821.f,
        GN_Point(0.f, 0.f, 0.f),
        1.5f,
        1.5f, // Just for debugMode
        0.007f,
        0.,
        0.,
        0.19,
        applicationPath.dirPath() + "../../assets/textures/CallistoMap.jpg",
        13,
        true
        );

    GN_Astrobject ganymede(applicationPath,
        "Ganymede",
        5262.f,
        GN_Point(0.f, 0.f, 0.f),
        2.f,
        2.f, // Just for debugMode
        0.001f,
        0.,
        0.,
        0.18,
        applicationPath.dirPath() + "../../assets/textures/GanymedeMap.jpg",
        14,
        true
        );

    GN_Astrobject europa(applicationPath,
        "Europa",
        3122.f, 
        GN_Point(0.f, 0.f, 0.f),
        3.f,
        3.f, // Just for debugMode
        0.009f,
        0.,
        0.,
        0.47,
        applicationPath.dirPath() + "../../assets/textures/EuropaMap.jpg",
        15,
        true
        );

    GN_Astrobject io(applicationPath,
        "Io",
        3643.f,
        GN_Point(0.f, 0.f, 0.f),
        4.f,
        4.f, // Just for debugMode
        0.004f,
        0.,
        0.,
        0.04,
        applicationPath.dirPath() + "../../assets/textures/IoMap.jpg",
        16,
        true
        );

    GN_Astrobject mimas(applicationPath,
        "Mimas",
        397.3f,
        GN_Point(0.f, 0.f, 0.f),
        2.5f,
        2.5f, // Just for debugMode
        0.0202f,
        0.,
        0.,
        1.53,
        applicationPath.dirPath() + "../../assets/textures/MimasMap.png",
        17,
        true
        );

    GN_Astrobject enceladus(applicationPath,
        "Enceladus",
        504.f,
        GN_Point(0.f, 0.f, 0.f),
        2.75f,
        2.75f, // Just for debugMode
        0.0045f,
        0.,
        0.,
        0.,
        applicationPath.dirPath() + "../../assets/textures/EnceladusMap.jpg",
        18,
        true
        );

    GN_Astrobject tethys(applicationPath,
        "Tethys",
        1061.3f,
        GN_Point(0.f, 0.f, 0.f),
        3.f,
        3.f, // Just for debugMode
        0.f,
        0.,
        0.,
        1.86,
        applicationPath.dirPath() + "../../assets/textures/TethysMap.jpg",
        19,
        true
        );

    GN_Astrobject dione(applicationPath,
        "Dione",
        1122.7f,
        GN_Point(0.f, 0.f, 0.f),
        3.5f,
        3.5f, // Just for debugMode
        0.0022f,
        0.,
        0.,
        0.02,
        applicationPath.dirPath() + "../../assets/textures/DioneMap.jpg",
        20,
        true
        );

    GN_Astrobject rhea(applicationPath,
        "Rhea",
        1526.7f,
        GN_Point(0.f, 0.f, 0.f),
        4.f,
        4.f, // Just for debugMode
        0.0010f,
        0.,
        0.,
        0.35,
        applicationPath.dirPath() + "../../assets/textures/RheaMap.jpg",
        21,
        true
        );

    GN_Astrobject titan(applicationPath,
        "Titan",
        2575.f,
        GN_Point(0.f, 0.f, 0.f),
        4.5f,
        4.5f, // Just for debugMode
        0.0292f,
        0.,
        0.,
        0.33,
        applicationPath.dirPath() + "../../assets/textures/TitanMap.jpg",
        22,
        true
        );

    GN_Astrobject hyperion(applicationPath,
        "Hyperion",
        277.3f,
        GN_Point(0.f, 0.f, 0.f),
        5.f,
        5.f, // Just for debugMode
        0.1042f,
        0.,
        0.,
        0.43,
        applicationPath.dirPath() + "../../assets/textures/HyperionMap.jpg",
        23,
        true
        );

    GN_Astrobject iapetus(applicationPath,
        "Iapetus",
        1468.7f,
        GN_Point(0.f, 0.f, 0.f),
        5.5f,
        5.5f, // Just for debugMode
        0.0283f,
        0.,
        0.,
        14.72,
        applicationPath.dirPath() + "../../assets/textures/IapetusMap.jpg",
        24,
        true
        );

    GN_Astrobject ariel(applicationPath,
        "Ariel",
        1157.8f,
        GN_Point(0.f, 0.f, 0.f),
        2.5f,
        2.5f, // Just for debugMode
        0.0012f,
        0.,
        0.,
        0.04,
        applicationPath.dirPath() + "../../assets/textures/ArielMap.jpg",
        25,
        true
        );

    GN_Astrobject umbriel(applicationPath,
        "Umbriel",
        1169.4f,
        GN_Point(0.f, 0.f, 0.f),
        2.75f,
        2.75f, // Just for debugMode
        0.0039f,
        0.,
        0.,
        0.13,
        applicationPath.dirPath() + "../../assets/textures/UmbrielMap.jpg",
        26,
        true
        );

    GN_Astrobject titania(applicationPath,
        "Titania",
        1577.8f,
        GN_Point(0.f, 0.f, 0.f),
        3.f,
        3.f, // Just for debugMode
        0.0011f,
        0.,
        0.,
        0.08,
        applicationPath.dirPath() + "../../assets/textures/TitaniaMap.jpg",
        27,
        true
        );

    GN_Astrobject oberon(applicationPath,
        "Oberon",
        1522.8f,
        GN_Point(0.f, 0.f, 0.f),
        3.5f,
        3.5f, // Just for debugMode
        0.0014f,
        0.,
        0.,
        0.07,
        applicationPath.dirPath() + "../../assets/textures/OberonMap.jpg",
        28,
        true
        );

    GN_Astrobject miranda(applicationPath,
        "Miranda",
        471.4f,
        GN_Point(0.f, 0.f, 0.f),
        4.f,
        4.f, // Just for debugMode
        0.0013f,
        0.,
        0.,
        4.34,
        applicationPath.dirPath() + "../../assets/textures/MirandaMap.jpg",
        29,
        true
        );

    GN_Astrobject triton(applicationPath,
        "Triton",
        2706.8f,
        GN_Point(0.f, 0.f, 0.f),
        3.f,
        3.f, // Just for debugMode
        0.000016f,
        0.,
        0.,
        157.345,
        applicationPath.dirPath() + "../../assets/textures/TritonMap.jpg",
        30,
        true
        );

    GN_Astrobject nereid(applicationPath,
        "Nereid",
        340.f,
        GN_Point(0.f, 0.f, 0.f),
        3.5f,
        3.5f, // Just for debugMode
        0.7512f,
        0.,
        0.,
        7.23,
        applicationPath.dirPath() + "../../assets/textures/NereidMap.jpg",
        31,
        true
        );

    GN_Astrobject charon(applicationPath,
        "Charon",
        1212, // radius = 606
        GN_Point(0.f, 0.f, 0.f),
        2.f,
        2.f, // Just for debugMode
        0.f,
        0.,
        0.,
        0.00005,
        applicationPath.dirPath() + "../../assets/textures/CharonMap.jpg",
        32,
        true
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

  saturn.generateAsteroidsMatrices();
  uranus.generateAsteroidsMatrices();

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
  uranus.bindTexture(textures);
  neptune.bindTexture(textures);
  pluto.bindTexture(textures);
  moon.bindTexture(textures);
  phobos.bindTexture(textures);
  deimos.bindTexture(textures);
  callisto.bindTexture(textures);
  ganymede.bindTexture(textures);
  europa.bindTexture(textures);
  io.bindTexture(textures);
  mimas.bindTexture(textures);
  enceladus.bindTexture(textures);
  tethys.bindTexture(textures);
  dione.bindTexture(textures);
  rhea.bindTexture(textures);
  titan.bindTexture(textures);
  hyperion.bindTexture(textures);
  iapetus.bindTexture(textures);
  ariel.bindTexture(textures);
  umbriel.bindTexture(textures);
  titania.bindTexture(textures);
  oberon.bindTexture(textures);
  miranda.bindTexture(textures);
  triton.bindTexture(textures);
  nereid.bindTexture(textures);
  charon.bindTexture(textures);

  // for rock too
	const GLenum min_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR...
	const GLenum mag_filter = GL_LINEAR; // GL_NEAREST, GL_LINEAR

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[NB_TEXTURES-1]); // Bind texture object
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, asterMapImage->getWidth(), asterMapImage->getHeight(), 0, GL_RGBA, GL_FLOAT, asterMapImage->getPixels()); // Load texture image
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture



  // Application loop:
  const float pan_motio_speed = 1.f;
  const float left_right_motion_speed = 100.f;

  bool done = false;
  bool animation = false;
  bool debugMode = false;
  float time = 0.f;
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
        case SDLK_t:
          animation = !animation;
          break;
        case SDLK_b:
          debugMode = !debugMode;
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
    if (animation){
      time = windowManager.getTime();
    }

    // Compute global matrices
    glm::mat4 global_MVMatrix = camera.getViewMatrix();

    // === SUN ===
    sun.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Mercury ===
    mercury.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === VENUS === 
    venus.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === EARTH === 
    glm::mat4 earthMVMatrix = earth.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === MARS === 
    glm::mat4 marsMVMatrix = mars.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Jupiter === 
    glm::mat4 jupiterMVMatrix = jupiter.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Saturn === 
    glm::mat4 saturnMVMatrix = saturn.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Uranus ===
    glm::mat4 uranusMVMatrix = uranus.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
    
    // === Neptune ===
    glm::mat4 neptuneMVMatrix = neptune.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
    
    // === Pluto ===
    glm::mat4 plutoMVMatrix = pluto.display(global_MVMatrix, SUN_DIAMETER, ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Earth satellites ====
    // === Moon ===
    moon.display(earthMVMatrix, earth.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Mars satellites ====
    // === Phobos ===
    phobos.display(marsMVMatrix, mars.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Deimos ===
    deimos.display(marsMVMatrix, mars.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Jupiter satellites ====
    // === Callisto ===
    callisto.display(jupiterMVMatrix, jupiter.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Ganymede ===
    ganymede.display(jupiterMVMatrix, jupiter.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
  
    // === Europa ===
    europa.display(jupiterMVMatrix, jupiter.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Io ===
    io.display(jupiterMVMatrix, jupiter.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Saturn satellites ====
    // === Mimas ===
    mimas.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Enceladus ===
    enceladus.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
  
    // === Tethys ===
    tethys.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Dione ===
    dione.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Rhea ===
    rhea.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Titan ===
    titan.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
  
    // === Hyperion ===
    hyperion.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Iapetus ===
    iapetus.display(saturnMVMatrix, saturn.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Uranus satellites ====
    // === Ariel ===
    ariel.display(uranusMVMatrix, uranus.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Umbriel ===
    umbriel.display(uranusMVMatrix, uranus.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // === Titania ===
    titania.display(uranusMVMatrix, uranus.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);
  
    // === Oberon ===
    oberon.display(uranusMVMatrix, uranus.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // // === Miranda ===
    miranda.display(uranusMVMatrix, uranus.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // ==== Neptune satellites ====
    // === Triton ===
    triton.display(neptuneMVMatrix, neptune.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    // === Nereid ===
    nereid.display(neptuneMVMatrix, neptune.getDiameter(), ProjMatrix, time*2, textures, sphere_nb_vertices, debugMode);

    // ==== Pluto satellites ====
    // === Charon ===
    charon.display(plutoMVMatrix, pluto.getDiameter(), ProjMatrix, time, textures, sphere_nb_vertices, debugMode);

    glBindVertexArray(0); // Unbind vao (from active VAO)
    // Update the display
    windowManager.swapBuffers();
  }

  glDeleteTextures(NB_TEXTURES, textures); // Release texture

  std::cout << "Closing application" << std::endl;
  return EXIT_SUCCESS;
}
