#include "PhysicsWorld.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "SphereColliderComponent.h"
#include "Collision.h"
#include "GameObject.h"
#include "Transform.h"

#include <algorithm>

void PhysicsWorld::SetGravity(const glm::vec3& gravity) {
    m_gravity = gravity;
}

void PhysicsWorld::AddBody(RigidbodyComponent* body) {
    if (body) m_bodies.push_back(body);
}

void PhysicsWorld::RemoveBody(RigidbodyComponent* body) {
    m_bodies.erase(std::remove(m_bodies.begin(), m_bodies.end(), body), m_bodies.end());
}

void PhysicsWorld::Step(float dt) {
    for (auto* body : m_bodies) {
        if (body->isStatic) continue;

        if (body->useGravity) {
            body->AddForce(m_gravity * dt); // F = ma (упрощенно v += g*dt)
        }

        // Интеграция позиции: x += v * dt
        Transform* transform = body->GetOwner()->GetTransformPtr();
        transform->Translate(body->velocity * dt);

        // Линейное сопротивление (Drag)
        body->velocity *= (1.0f - body->drag * dt);
    }

    // 2. Проверка коллизий (Все со всеми)
    for (size_t i = 0; i < m_bodies.size(); ++i) {
        for (size_t j = i + 1; j < m_bodies.size(); ++j) {
            RigidbodyComponent* rbA = m_bodies[i];
            RigidbodyComponent* rbB = m_bodies[j];

            // Два статических объекта не взаимодействуют
            if (rbA->isStatic && rbB->isStatic) continue;

            ResolveCollision(rbA, rbB);
        }
    }
}

void PhysicsWorld::ResolveCollision(RigidbodyComponent* rbA, RigidbodyComponent* rbB) {
    auto* colA = rbA->GetOwner()->GetComponent<ColliderComponent>();
    auto* colB = rbB->GetOwner()->GetComponent<ColliderComponent>();

    if (!colA || !colB) return; 

    Transform* transA = rbA->GetOwner()->GetTransformPtr();
    Transform* transB = rbB->GetOwner()->GetTransformPtr();

    CollisionResult result;

    if (colA->GetColliderType() == ColliderType::Box) {
        auto* boxA = static_cast<BoxColliderComponent*>(colA);

        if (colB->GetColliderType() == ColliderType::Box) {
            auto* boxB = static_cast<BoxColliderComponent*>(colB);
            result = Collision::BoxVsBox(*boxA, transA, *boxB, transB);
        }
        else if (colB->GetColliderType() == ColliderType::Sphere) {
            auto* sphereB = static_cast<SphereColliderComponent*>(colB);
            result = Collision::SphereVsBox(*sphereB, transB, *boxA, transA);
            if (result.isColliding) result.normal = -result.normal; // Разворачиваем нормаль
        }
    }
    else if (colA->GetColliderType() == ColliderType::Sphere) {
        auto* sphereA = static_cast<SphereColliderComponent*>(colA);

        if (colB->GetColliderType() == ColliderType::Sphere) {
            auto* sphereB = static_cast<SphereColliderComponent*>(colB);
            result = Collision::SphereVsSphere(*sphereA, transA, *sphereB, transB);
        }
        else if (colB->GetColliderType() == ColliderType::Box) {
            auto* boxB = static_cast<BoxColliderComponent*>(colB);
            result = Collision::SphereVsBox(*sphereA, transA, *boxB, transB);
        }
    }

    if (result.isColliding) {
        ApplyCollisionResponse(rbA, rbB, result);
    }
}

void PhysicsWorld::ApplyCollisionResponse(RigidbodyComponent* rbA, RigidbodyComponent* rbB, const CollisionResult& res) {
    Transform* tA = rbA->GetOwner()->GetTransformPtr();
    Transform* tB = rbB->GetOwner()->GetTransformPtr();

    const float percent = 0.8f;
    const float slop = 0.01f;
    glm::vec3 correction = res.normal * percent * std::max(res.depth - slop, 0.0f);

    if (rbA->isStatic) {
        tB->Translate(correction);
    }
    else if (rbB->isStatic) {
        tA->Translate(-correction);
    }
    else {
        tA->Translate(-correction * 0.5f);
        tB->Translate(correction * 0.5f);
    }

    glm::vec3 relativeVel = rbB->velocity - rbA->velocity;
    float velAlongNormal = glm::dot(relativeVel, res.normal);

    if (velAlongNormal > 0) return;

    auto* colA = rbA->GetOwner()->GetComponent<ColliderComponent>();
    auto* colB = rbB->GetOwner()->GetComponent<ColliderComponent>();
    float e = std::min(colA->restitution, colB->restitution);

    float j = -(1 + e) * velAlongNormal;

    float invMassA = rbA->isStatic ? 0 : 1.0f / rbA->mass;
    float invMassB = rbB->isStatic ? 0 : 1.0f / rbB->mass;

    j /= (invMassA + invMassB);

    glm::vec3 impulse = j * res.normal;

    if (!rbA->isStatic) rbA->velocity -= impulse * invMassA;
    if (!rbB->isStatic) rbB->velocity += impulse * invMassB;

    // --- Флаги onGround ---
    // Если нормаль выталкивания направлена вверх (Y+), значит rbA стоит на rbB
    // res.normal направлена от A к B (или наоборот, зависит от реализации Collision)
    // В моей реализации BoxVsBox: нормаль от A к B.
    // Если нормаль (0, 1, 0), значит B находится СВЕРХУ A.

    if (res.normal.y > 0.7f && rbA->isStatic) rbB->onGround = true; // B стоит на статичном A
    if (res.normal.y < -0.7f && rbB->isStatic) rbA->onGround = true; // A стоит на статичном B
}