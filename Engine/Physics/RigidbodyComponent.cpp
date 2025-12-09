#include "RigidbodyComponent.h"

void RigidbodyComponent::AddForce(const glm::vec3 force) {
	if (isStatic) return;

	velocity += force / mass;
}

void RigidbodyComponent::AddImpulse(const glm::vec3& impulse) {
	if (isStatic) return;

	velocity += impulse / mass;
}

void RigidbodyComponent::Stop() {
	velocity = glm::vec3(0.0f);
}