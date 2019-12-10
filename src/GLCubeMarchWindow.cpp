#include "GLCubeMarchWindow.hpp"

#include <iostream>

#define CLEAR_COLOR 0x1e3356

void GLCubeMarchWindow::framebufferResized() {
	glViewport(0, 0, m_width, m_height);
}

GLCubeMarchWindow::GLCubeMarchWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_width = 800;
	m_height = 600;

	m_window = glfwCreateWindow(m_width, m_height, "OpenGL Cubemarch", NULL, NULL);
	if (m_window == NULL) {
		std::cerr << "Couldn't get a GLFW window" << std::endl;
		glfwTerminate();
		m_setupStatus = -1;
		return;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't initialise GLAD" << std::endl;
		m_setupStatus = -1;
		return;
	}

	glViewport(0, 0, m_width, m_height);

	auto testMesh = std::make_shared<PlainMesh>();
	std::shared_ptr<std::vector<Vertex>> vertices(new std::vector<Vertex> {
		std::vector<Vertex> {
			Vertex {
				Position: {-0.5, -0.5, 0.0},
				Normal: {0.0, 0.0, 0.0},
				TexCoords: {0.0, 0.0}
			},
			Vertex {
				Position: {0.0, 0.5, 0.0},
				Normal: {0.0, 0.0, 0.0},
				TexCoords: {0.0, 0.0}
			},
			Vertex {
				Position: {0.5, -0.5, 0.0},
				Normal: {0.0, 0.0, 0.0},
				TexCoords: {0.0, 0.0}
			}
		}
	});
	std::shared_ptr<std::vector<unsigned int>> indices(new std::vector<unsigned int> {
		0, 1, 2
	});
	testMesh->SetBuffers(std::move(vertices), std::move(indices));
	m_meshes.push_back(testMesh);

	m_shaders.push_back(Shader("StandardShaderV.glsl", "StandardShaderF.glsl"));

	m_setupStatus = 0;
}

int GLCubeMarchWindow::Run() {
	if (m_setupStatus != 0)
		return -1;

	int oldWidth, oldHeight;
	oldWidth = m_width;
	oldHeight = m_height;
	bool shouldClose = false;
	m_shaders.at(0).Use();
	while (!shouldClose) {
		glClearColor((double)((CLEAR_COLOR&0xFF0000)>>16)/(double)256, (double)((CLEAR_COLOR&0xFF00)>>8)/(double)256, (double)(CLEAR_COLOR&0xFF)/(double)256, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto mesh : m_meshes) {
			mesh->Draw();
		}

		// Detect window resize
		glfwGetFramebufferSize(m_window, &m_width, &m_height);
		if (m_width != oldWidth || m_height != oldHeight) {
			framebufferResized();
		}
		// Detect if window should close
		shouldClose = glfwWindowShouldClose(m_window) ||
			glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}

GLCubeMarchWindow::~GLCubeMarchWindow() {
	glfwTerminate();
}