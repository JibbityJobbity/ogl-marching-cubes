#include <iostream>
#include "GLCubeMarchWindow.hpp"

int main() {
	GLCubeMarchWindow w;

	if (w.Run()) {
		std::cerr << "Error!" << std::endl;
		return -1;
	}

	return 0;
}