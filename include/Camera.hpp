#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera();

	void Move(float x, float y, float z);
	void Rotate(float yaw, float pitch, float roll);
	void SetPos(float x, float y, float z);
	void SetRotation(float yaw, float pitch, float roll);
	glm::mat4 GetProj();
	glm::mat4 GetView();
	void SetProjProps(float aspectRatio, float fov);

protected:
	glm::vec3 front();

	glm::vec3 m_up;
	glm::vec3 m_pos;
	glm::vec3 m_rot;

	glm::mat4 m_view;
	glm::mat4 m_proj;
};

#endif