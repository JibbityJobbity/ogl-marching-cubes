#include "PlainMesh.hpp"
#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <string>

PlainMesh::PlainMesh() {
	buffersInitialised = false;

	customShader = {};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	standardShader = createShaderFromFile("StandardShaderV.glsl", "StandardShaderF.glsl");
}

PlainMesh::~PlainMesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void PlainMesh::Draw() {
	if (!buffersInitialised)
		return;

	glBindVertexArray(VAO);

	if (drawMode == DrawMode::Standard)
		glUseProgram(standardShader);
	else if (drawMode == DrawMode::NormalToColor)
		glUseProgram(normalToColorShader);
	else if (drawMode == DrawMode::Custom) {
		if (!customShader.has_value()) {
			std::cerr << "Can't draw custom shaded element without setting custom shader" << std::endl;
			return;
		}
		glUseProgram(customShader.value());
	}

	glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

unsigned int PlainMesh::createShaderFromFile(std::string vsPath, std::string fsPath) {
	std::string vsSrc, fsSrc, str;
	std::ifstream vsFile(vsPath);
	std::ifstream fsFile(fsPath);
	while (std::getline(vsFile, str)) {
		vsSrc += str + '\n';
	}
	while (std::getline(fsFile, str)) {
		fsSrc += str + '\n';
	}

	return createShaderFromSource(vsSrc.c_str(), fsSrc.c_str());
}

unsigned int PlainMesh::createShaderFromSource(const char* vsSource, const char* fsSource) {
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vsSource, NULL);
	glCompileShader(vShader);

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fsSource, NULL);
	glCompileShader(fShader);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	int success = 0;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "---SHADER ERROR---" << std::endl
			<< infoLog << std::endl;
	}

	return program;
}

void PlainMesh::SetCustomShader(const char* source) {
	// TODO
	std::cerr << "Custom shader is TODO" << std::endl;
}

void PlainMesh::SetDrawMode(DrawMode d) {
	drawMode = d;
}

void PlainMesh::bindBuffers() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void PlainMesh::SetBuffers(std::shared_ptr<std::vector<Vertex>> vertices, std::shared_ptr<std::vector<unsigned int>> indices) {
	bindBuffers();
	m_vertices = vertices;
	m_indices = indices;

	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), vertices->data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	buffersInitialised = true;

	glBindVertexArray(0);
}
