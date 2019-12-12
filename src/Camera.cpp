#include "Camera.hpp"

#include <iostream>

Camera::Camera() {
	m_up = glm::vec3(0.0, 1.0, 0.0);
	m_rot = glm::vec3(0.0, 0.0, 0.0);
	m_pos = glm::vec3(0.0, 0.0, -3.0);

	m_view = glm::translate(glm::mat4(1.0f), m_pos);
	m_proj = glm::perspective(
		glm::radians(75.0f), 
		(float)800/(float)600, 
		0.1f, 
		1000.0f
	);
}

glm::vec3 Camera::front() {
	glm::vec3 front;

	front.x = sin(m_rot.y) * cos(m_rot.x);
	front.y = sin(m_rot.x);
	front.z = cos(m_rot.y) * cos(m_rot.x);

	return front;
}

void Camera::Move(float x, float y, float z) {
	m_pos.x -= cos(m_rot.y) * x;
	m_pos.z += sin(m_rot.y) * x;

	m_pos.x -= sin(m_rot.y) * z;
	m_pos.z -= cos(m_rot.y) * z;

	m_pos.y += y;

	glm::vec3 f = front();

	m_view = glm::lookAt(m_pos, m_pos + front(), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::Rotate(float yaw, float pitch, float roll) {
	m_rot += glm::vec3(
		glm::radians(pitch), 
		glm::radians(yaw), 
		glm::radians(roll)
	);

	m_view = glm::lookAt(m_pos, m_pos + front(), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::SetPos(float x, float y, float z) {
	m_pos = glm::vec3(x, y, z);
}

void Camera::SetRotation(float yaw, float pitch, float roll) {
	m_pos = glm::vec3(yaw, pitch, roll);
}

glm::mat4 Camera::GetProj() {
	return m_proj;
}

glm::mat4 Camera::GetView() {
	return m_view;
}

void Camera::SetProjProps(float aspectRatio, float fov) {
	m_proj = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);
}