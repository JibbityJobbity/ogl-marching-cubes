#include "Shader.hpp"

#include "glad/glad.h"

#include <fstream>
#include <iostream>

Shader::Shader(std::string vsPath, std::string fsPath) {
	std::string vsSrc, fsSrc, str;
	std::ifstream vsFile(vsPath);
	std::ifstream fsFile(fsPath);
	while (std::getline(vsFile, str)) {
		vsSrc += str + '\n';
	}
	while (std::getline(fsFile, str)) {
		fsSrc += str + '\n';
	}

	const char* pVsSrc = vsSrc.c_str();
	const char* pFsSrc = fsSrc.c_str();

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &pVsSrc, NULL);
	glCompileShader(vShader);

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &pFsSrc, NULL);
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

	m_program = program;
}

void Shader::Use() {
	glUseProgram(m_program);
}

void Shader::SetMat4(std::string key, glm::mat4 value) {
	unsigned int uniformLocation = glGetUniformLocation(m_program, key.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}