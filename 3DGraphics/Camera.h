#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

float yaw = -90.0f;
float pitch = 0.0f;

class Camera {
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float fov;
	float aspectRatio;
	float nearPlane;
	float farPlane;
public:
	Camera(glm::vec3 position) :
		position(0.0f, 0.0f, 3.0f),
		front(0.0f, 0.0f, -1.0f),
		up(0.0f, 1.0f, 0.0f),
		fov(45.0f),
		aspectRatio(4.0f / 3.0f),
		nearPlane(0.1f),
		farPlane(100.0f) {}

	glm::mat4 getViewMatrix() const {
		glm::vec3 target = position + front;
		return glm::lookAt(position, target, up);
	}

	glm::mat4 getProjectionMatrix() const {
		return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	void processKeyboard(Camera_Movement direction, float deltaTime) {
		float velocity = 2.5f * deltaTime;
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= glm::normalize(glm::cross(front, up)) * velocity;
		if (direction == RIGHT)
			position += glm::normalize(glm::cross(front, up)) * velocity;
	}

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (constrainPitch) {
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}
		updateCameraVectors();
	}

private:
	void updateCameraVectors() {
		glm::vec3 newFront(1.0f, 0.0f, 0.0f);
		newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFront.y = sin(glm::radians(pitch));
		newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(newFront);
	}
};

#endif // !CAMERA_H

