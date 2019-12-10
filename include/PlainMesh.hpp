#ifndef PLAINMESH_HPP
#define PLAINMESH_HPP

#include <glm/glm.hpp>

#include <optional>
#include <vector>
#include <memory>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class PlainMesh {
public:
	PlainMesh();
	~PlainMesh();

	void Draw();
	void SetBuffers(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<unsigned int>> indices);
protected:

	unsigned int VAO, VBO, EBO;
	bool buffersInitialised;
	std::shared_ptr<std::vector<Vertex>> m_vertices;
	std::shared_ptr<std::vector<unsigned int>> m_indices;

	unsigned int createShaderFromFile(std::string vsPath, std::string fsPath);
	unsigned int createShaderFromSource(const char* vsSource, const char* fsSource);
	void bindBuffers();
};

#endif