#include "Collision.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "Transform.h" 
#include <cmath>
#include <algorithm> 

CollisionResult Collision::SphereVsSphere(
    const SphereColliderComponent& s1, Transform* t1,
    const SphereColliderComponent& s2, Transform* t2)
{
    CollisionResult result;

    glm::vec3 p1 = t1->GetPosition() + s1.centerOffset;
    glm::vec3 p2 = t2->GetPosition() + s2.centerOffset;

    float r1 = s1.GetWorldRadius();
    float r2 = s2.GetWorldRadius();

    glm::vec3 delta = p2 - p1;
    float distance = glm::length(delta);

    float radiusSum = r1 + r2;

    if (distance < radiusSum) {
        result.isColliding = true;
        result.depth = radiusSum - distance;

        if (distance > 0.0001f) {
            result.normal = glm::normalize(delta);
        }
        else {
            result.normal = glm::vec3(0, 1, 0);
        }
    }

    return result;
}

CollisionResult Collision::SphereVsBox(
    const SphereColliderComponent& sphere, Transform* tSphere,
    const BoxColliderComponent& box, Transform* tBox)
{
    CollisionResult result;

    glm::vec3 sphereCenter = tSphere->GetPosition() + sphere.centerOffset;
    float radius = sphere.GetWorldRadius();

    glm::vec3 boxCenter = tBox->GetPosition() + box.centerOffset;
    glm::vec3 boxHalfSize = box.GetSize();

    glm::vec3 minAABB = boxCenter - boxHalfSize;
    glm::vec3 maxAABB = boxCenter + boxHalfSize;
    
    glm::vec3 closestPoint = glm::vec3(
        std::clamp(sphereCenter.x, minAABB.x, maxAABB.x),
        std::clamp(sphereCenter.y, minAABB.y, maxAABB.y),
        std::clamp(sphereCenter.z, minAABB.z, maxAABB.z)
    );

    glm::vec3 delta = closestPoint - sphereCenter;
    float distanceSquared = glm::dot(delta, delta);

    if (distanceSquared < (radius * radius)) {
        result.isColliding = true;

        float distance = std::sqrt(distanceSquared);

        result.depth = radius - distance;

        if (distance > 0.0001f) {
            result.normal = glm::normalize(delta); 
        }
        else {
            result.normal = glm::vec3(0, 1, 0);
        }
    }

    return result;
}

CollisionResult Collision::BoxVsBox(
    const BoxColliderComponent& b1, Transform* t1,
    const BoxColliderComponent& b2, Transform* t2)
{
    CollisionResult result;

    glm::vec3 p1 = t1->GetPosition() + b1.centerOffset;
    glm::vec3 p2 = t2->GetPosition() + b2.centerOffset;
    
    glm::vec3 half1 = b1.GetSize();
    glm::vec3 half2 = b2.GetSize();

    glm::vec3 delta = p2 - p1;

    float overlapX = (half1.x + half2.x) - std::abs(delta.x);
    if (overlapX <= 0) return result; 

    float overlapY = (half1.y + half2.y) - std::abs(delta.y);
    if (overlapY <= 0) return result; 

    float overlapZ = (half1.z + half2.z) - std::abs(delta.z);
    if (overlapZ <= 0) return result; 

    result.isColliding = true;

    if (overlapX < overlapY && overlapX < overlapZ) {
        result.depth = overlapX;
        result.normal = glm::vec3((delta.x > 0) ? 1.0f : -1.0f, 0.0f, 0.0f);
    }
    else if (overlapY < overlapZ) {
        result.depth = overlapY;
        result.normal = glm::vec3(0.0f, (delta.y > 0) ? 1.0f : -1.0f, 0.0f);
    }
    else {
        result.depth = overlapZ;
        result.normal = glm::vec3(0.0f, 0.0f, (delta.z > 0) ? 1.0f : -1.0f);
    }

    return result;
}