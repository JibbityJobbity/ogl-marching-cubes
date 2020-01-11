cmake_minimum_required(VERSION 3.16.0)
set (CMAKE_CXX_STANDARD 17)
project(OGLCubeMarch)

set(SOURCES 
	src/main.cpp
	src/GLCubeMarchWindow.cpp
	src/PlainMesh.cpp
	src/Shader.cpp
	src/Camera.cpp
	src/PerlinNoise.cpp
	src/ThreeDimensionMesh.cpp
	src/glad.c
)

add_executable(OGLCubeMarch ${SOURCES})
target_link_libraries(OGLCubeMarch glfw GL X11 pthread Xrandr Xi dl)
target_include_directories(OGLCubeMarch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)