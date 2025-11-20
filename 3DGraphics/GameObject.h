#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Mesh.h"

struct GameObject {
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float rotationSpeed;
	float scale;

	Mesh* mesh;

	GameObject() : 
		position(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), rotationSpeed(0.0f), scale(1.0f), mesh(nullptr) {}

	void draw(const Shader& shader, float time) const {
		if (!mesh) return;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);

		float angle = time * rotationSpeed;
		model = glm::rotate(model, angle, rotationAxis);

		model = glm::scale(model, glm::vec3(scale));

		shader.setMat4("model", model);
		mesh->Draw();
	}
};

#endif