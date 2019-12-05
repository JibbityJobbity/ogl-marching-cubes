#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CLEAR_COLOR 0x1e3356

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cubemarch", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Couldn't get a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't initialise GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	bool shouldClose = false;
	while (!shouldClose) {
		glClearColor((double)((CLEAR_COLOR&0xFF0000)>>16)/(double)256, (double)((CLEAR_COLOR&0xFF00)>>8)/(double)256, (double)(CLEAR_COLOR&0xFF)/(double)256, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		shouldClose = glfwWindowShouldClose(window) ||
			glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	}

    glfwTerminate();
	return 0;
}