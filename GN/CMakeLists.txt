include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)


add_executable(GN_visualizer ${SRC_FILES} ${SHADER_FILES})
target_compile_features(GN_visualizer PRIVATE cxx_std_17)
target_link_libraries(GN_visualizer ${ALL_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
