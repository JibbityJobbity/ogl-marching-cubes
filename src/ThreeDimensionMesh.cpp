#include "ThreeDimensionMesh.hpp"

#include <iostream>

ThreeDimensionMesh::ThreeDimensionMesh() {
	auto mesh = std::make_shared<std::vector<Vertex>>();

	PerlinNoise n(time(nullptr));

	for (int x = 0; x < GRID_SIZE - 1; x++) {
		for (int z = 0; z < GRID_SIZE - 1; z++) {
			for (int y = 0; y < GRID_SIZE - 1; y++) {
				unsigned char cubeCorners = 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x)*NOISE_SCALE_X, ((double)y)*NOISE_SCALE_Y, ((double)z)*NOISE_SCALE_Z) ? 1 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x + 1)*NOISE_SCALE_X, ((double)y)*NOISE_SCALE_Y, ((double)z)*NOISE_SCALE_Z) ? 2 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x + 1)*NOISE_SCALE_X, ((double)y)*NOISE_SCALE_Y, ((double)z + 1)*NOISE_SCALE_Z) ? 4 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x)*NOISE_SCALE_X, ((double)y)*NOISE_SCALE_Y, ((double)z + 1)*NOISE_SCALE_Z) ? 8 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x)*NOISE_SCALE_X, ((double)y + 1)*NOISE_SCALE_Y, ((double)z)*NOISE_SCALE_Z) ? 16 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x + 1)*NOISE_SCALE_X, ((double)y + 1)*NOISE_SCALE_Y, ((double)z)*NOISE_SCALE_Z) ? 32 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x + 1)*NOISE_SCALE_X, ((double)y + 1)*NOISE_SCALE_Y, ((double)z + 1)*NOISE_SCALE_Z) ? 64 : 0;
				cubeCorners |= NOISE_THRESHOLD < n.noise(((double)x)*NOISE_SCALE_X, ((double)y + 1)*NOISE_SCALE_Y, ((double)z + 1)*NOISE_SCALE_Z) ? 128 : 0;

				for (int i = 0; i < cellShapes[cubeCorners].size(); i++) {
					Vertex v = {
						Position: edgePositions[cellShapes[cubeCorners][i]],
						Normal: glm::vec3(0.0, 0.0, 0.0),
						TexCoords: glm::vec2(0.0, 0.0),
					};
					v.Position.x += x;
					v.Position.y += y;
					v.Position.z += z;
					mesh->push_back(v);
					if (i % 3 == 2) {
						glm::vec3 U = mesh->at(mesh->size()-2).Position - mesh->at(mesh->size()-3).Position;
						glm::vec3 V = mesh->at(mesh->size()-1).Position - mesh->at(mesh->size()-3).Position;
						glm::vec3 normal;
						normal.x = ((U.y*V.z) - (U.z*V.y));
						normal.y = ((U.z*V.x) - (U.x*V.z));
						normal.z = ((U.x*V.y) - (U.y*V.x));
						normal = glm::normalize(normal);
						normal.x = normal.x / 2 + 0.5;
						normal.y = normal.y / 2 + 0.5;
						normal.z = normal.z / 2 + 0.5;
						mesh->at(mesh->size()-3).Normal = normal;
						mesh->at(mesh->size()-2).Normal = normal;
						mesh->at(mesh->size()-1).Normal = normal;
					}
				}
			}
		}
	}

	auto indices = std::make_shared<std::vector<unsigned int>>();
	indices->reserve(mesh->size());
	for (unsigned int i = 0; i < mesh->size(); i++) {
		indices->push_back(i);
	}

	SetBuffers(mesh, indices);
}