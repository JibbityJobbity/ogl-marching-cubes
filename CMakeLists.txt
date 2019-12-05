cmake_minimum_required(VERSION 3.16.0)
project(OGLCubeMarch)

set(SOURCES 
	src/main.cpp 
	src/glad.c 
)

add_executable(OGLCubeMarch ${SOURCES})
target_link_libraries(OGLCubeMarch glfw GL X11 pthread Xrandr Xi dl)
target_include_directories(OGLCubeMarch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)