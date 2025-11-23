#include "GameObject.h"

void GameObject::draw(const Shader& shader, float time) const {
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