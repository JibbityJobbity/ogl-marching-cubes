#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
public:
	Shader(std::string vsPath, std::string fsPath);
	//Shader(std::string vsPath, std::string fsPath, std::string gsPath);

	void Use();
protected:
	unsigned int m_program;
};

#endif