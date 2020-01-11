#include "GLCubeMarchWindow.hpp"

#include "ThreeDimensionMesh.hpp"

#include <iostream>

#define CLEAR_COLOR 0x1e3356

void GLCubeMarchWindow::framebufferResized() {
	glViewport(0, 0, m_width, m_height);
	m_camera.SetProjProps((float)m_width/(float)m_height, 75.0);
}

void GLCubeMarchWindow::processInput() {
	double now = glfwGetTime();
	double dTime = now - oldFrameTime;
	oldFrameTime = now;
	processMouse(dTime * 50);
	processKeyboard(dTime * 20);
}

void GLCubeMarchWindow::processMouse(double dTime) {
	double mouseX, mouseY;
	glfwGetCursorPos(m_window, &mouseX, &mouseY);

	if (firstMouseMove) {
		firstMouseMove = false;
		oldMouseX = mouseX;
		oldMouseY = mouseY;
		return;
	}

	if (oldMouseX != mouseX || oldMouseY != mouseY) {
		double dX = oldMouseX - mouseX;
		double dY = oldMouseY - mouseY;

		m_camera.Rotate(dX * 0.1f, dY * 0.1f, 0.0f);
	}

	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

void GLCubeMarchWindow::processKeyboard(double dTime) {
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera.Move(0.0, 0.0, -dTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera.Move(-dTime, 0.0, 0.0);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera.Move(0.0, 0.0, dTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera.Move(dTime, 0.0, 0.0);
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_camera.Move(0.0, dTime, 0.0);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_camera.Move(0.0, -dTime, 0.0);
	if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS &&
		glfwGetKey(m_window, GLFW_KEY_2) != GLFW_PRESS)
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	if (glfwGetKey(m_window, GLFW_KEY_1) != GLFW_PRESS &&
		glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

GLCubeMarchWindow::GLCubeMarchWindow() {
	firstMouseMove = true;
	oldFrameTime = glfwGetTime();

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
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't initialise GLAD" << std::endl;
		m_setupStatus = -1;
		return;
	}

	glViewport(0, 0, m_width, m_height);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

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
	//m_meshes.push_back(testMesh);
	m_meshes.push_back(std::make_shared<ThreeDimensionMesh>());

	m_shaders.push_back(Shader("StandardShaderV.glsl", "StandardShaderF.glsl"));

	m_camera = Camera();
	m_camera.SetProjProps((float)m_width/(float)m_height, 75.0);

	m_setupStatus = 0;
}

int GLCubeMarchWindow::Run() {
	int framecount = 0;
	float oldFramecountTime = glfwGetTime();
	if (m_setupStatus != 0)
		return -1;

	int oldWidth, oldHeight;
	bool shouldClose = false;
	while (!shouldClose) {
		glClearColor((double)((CLEAR_COLOR&0xFF0000)>>16)/(double)256, (double)((CLEAR_COLOR&0xFF00)>>8)/(double)256, (double)(CLEAR_COLOR&0xFF)/(double)256, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Process user input
		processInput();
		m_shaders.at(0).Use();
		m_shaders.at(0).SetMat4("camera", m_camera.GetProj() * m_camera.GetView());

		for (auto mesh : m_meshes) {
			mesh->Draw();
		}

		oldWidth = m_width;
		oldHeight = m_height;
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

		framecount++;
		if (glfwGetTime() - oldFramecountTime > 1.0f) {
			std::cout << framecount << std::endl;
			framecount = 0;
			oldFramecountTime = glfwGetTime();
		}
	}

	return 0;
}

GLCubeMarchWindow::~GLCubeMarchWindow() {
	glfwTerminate();
}