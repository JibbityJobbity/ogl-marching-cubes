#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "PlainMesh.hpp"

#include <vector>
#include <memory>

class GLCubeMarchWindow {
public:
	GLCubeMarchWindow();
	~GLCubeMarchWindow();
	int Run();

protected:
	void framebufferResized();

	std::vector<std::shared_ptr<PlainMesh>> m_meshes;
	int m_setupStatus;
	int m_width;
	int m_height;
	GLFWwindow* m_window;
};