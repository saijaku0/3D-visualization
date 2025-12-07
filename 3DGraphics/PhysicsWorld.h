#pragma once
#include <vector>
#include <glm/glm.hpp>

class GameObject;
class RigidbodyComponent;
struct CollisionResult;

class PhysicsWorld {
	std::vector<RigidbodyComponent*> m_bodies;
	glm::vec3 m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);
public:
	PhysicsWorld() = default;

	void SetGravity(const glm::vec3& gravity);

	void AddBody(RigidbodyComponent* body);
	void RemoveBody(RigidbodyComponent* body);

	void Step(float dt);
private:
	void ApplyCollisionResponse(RigidbodyComponent* rbA, RigidbodyComponent* rbB, const CollisionResult& res);
	void ResolveCollision(RigidbodyComponent* rbA, RigidbodyComponent* rbB);
};

