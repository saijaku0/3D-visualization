#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Mesh.h"

struct GameObject {
	glm::vec3 position;
	glm::vec3 rotationAxis;
	glm::vec3 scale;
	glm::vec3 color;
	glm::vec3 velocity;

	float angle;
	float rotationSpeed;
	bool isStatic;
	bool onGround;

	Mesh* mesh;

	GameObject() :
		position(0.0f),
		rotationAxis(0.0f, 1.0f, 0.0f),
		rotationSpeed(0.0f),
		scale(1.0f, 1.0f, 1.0f),
		angle(0.0f),
		color(1.0f, 1.0f, 1.0f),
		velocity(0.0f),
		isStatic(true),
		onGround(false),
		mesh(nullptr) {}

	void draw(const Shader& shader, float time) const;
};

#endif