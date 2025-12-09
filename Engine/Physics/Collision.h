#pragma once
#include <glm/glm.hpp>

class BoxColliderComponent;
class SphereColliderComponent;
class Transform;

struct CollisionResult {
    bool isColliding = false;
    glm::vec3 normal = glm::vec3(0.0f); 
    float depth = 0.0f;                 
};

class Collision {
public:
    static CollisionResult SphereVsSphere(
        const SphereColliderComponent& s1, Transform* t1,
        const SphereColliderComponent& s2, Transform* t2
    );

    static CollisionResult SphereVsBox(
        const SphereColliderComponent& sphere, Transform* tSphere,
        const BoxColliderComponent& box, Transform* tBox
    );

    static CollisionResult BoxVsBox(
        const BoxColliderComponent& b1, Transform* t1,
        const BoxColliderComponent& b2, Transform* t2
    );
};