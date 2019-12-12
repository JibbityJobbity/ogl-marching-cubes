#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "PlainMesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include <vector>
#include <memory>

class GLCubeMarchWindow {
public:
	GLCubeMarchWindow();
	~GLCubeMarchWindow();
	int Run();

protected:
	void framebufferResized();
	void processInput();
	void processMouse(double dTime);
	void processKeyboard(double dTime);

	std::vector<std::shared_ptr<PlainMesh>> m_meshes;
	int m_setupStatus;
	int m_width;
	int m_height;
	float oldMouseX, oldMouseY;
	double oldFrameTime;
	bool firstMouseMove;
	std::vector<Shader> m_shaders;
	Camera m_camera;
	GLFWwindow* m_window;
};