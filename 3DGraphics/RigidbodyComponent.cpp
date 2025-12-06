#include "RigidbodyComponent.h"

void RigidbodyComponent::AddForce(const glm::mat4 force) {
	if (isStatic) return;

	velocity += force / mass;
}

void RigidbodyComponent::Stop() {
	velocity = glm::vec3(0.0f);
}