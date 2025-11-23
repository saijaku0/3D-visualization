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

class Camera {
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float fov;
	float aspectRatio;
	float nearPlane;
	float farPlane;
public:
	Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f)) :
		front(0.0f, 0.0f, -1.0f),
		up(0.0f, 1.0f, 0.0f),
		fov(45.0f),
		aspectRatio(4.0f / 3.0f),
		nearPlane(0.1f),
		farPlane(100.0f) 
	{
		position = startPosition;
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		pitch = 0.0f;
		yaw = -90.0f;
		updateCameraVectors();
	}

	glm::mat4 getViewMatrix() const {
		glm::vec3 target = position + front;
		return glm::lookAt(position, target, up);
	}

	glm::mat4 getProjectionMatrix() const {
		return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	glm::vec3 getPosition() const {
		return position;
	}

	glm::vec3 getFront() const {
		return front;
	}

	void setPosition(const glm::vec3& newPosition) {
		position = newPosition;
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
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};

#endif // !CAMERA_H

