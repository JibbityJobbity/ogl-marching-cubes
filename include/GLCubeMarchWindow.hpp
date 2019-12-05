#include "glad/glad.h"
#include <GLFW/glfw3.h>

class GLCubeMarchWindow {
public:
	GLCubeMarchWindow();
	~GLCubeMarchWindow();
	int Run();

protected:
	void framebufferResized();

	int m_setupStatus;
	int m_width;
	int m_height;
	GLFWwindow* m_window;
};