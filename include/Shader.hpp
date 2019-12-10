#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(std::string vsPath, std::string fsPath);
	//Shader(std::string vsPath, std::string fsPath, std::string gsPath);

	void Use();
	void SetMat4(std::string key, glm::mat4 value);
protected:
	unsigned int m_program;
};

#endif