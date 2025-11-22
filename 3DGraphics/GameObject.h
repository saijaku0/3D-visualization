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

	float angle;
	float rotationSpeed;

	Mesh* mesh;

	GameObject() : 
		position(0.0f), 
		rotationAxis(0.0f, 1.0f, 0.0f), 
		rotationSpeed(0.0f), 
		scale(1.0f, 1.0f, 1.0f), 
		angle(0.0f),
		color(1.0f, 1.0f, 1.0f),
		mesh(nullptr) {}

	void draw(const Shader& shader, float time) const {
		if (!mesh) return;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);

		if (glm::length(rotationAxis) > 0.0f) {
			float initialRotation = angle + (time * rotationSpeed);
			model = glm::rotate(model, glm::radians(initialRotation), rotationAxis);
		}

		model = glm::scale(model, scale);

		shader.setMat4("model", model);
		shader.setVec3("objectColor", color);

		mesh->Draw();
	}
};

#endif