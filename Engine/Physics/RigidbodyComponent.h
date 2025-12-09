#pragma once
#include "../Core/Component.h"
#include <glm/glm.hpp>

class RigidbodyComponent :
    public Component {
public:
    glm::vec3 velocity = glm::vec3(0.0f);
    float mass = 1.0f;
    float drag = 0.4f;
    float restitution = 0.0f;

    bool isStatic = false;
    bool useGravity = true;
    bool onGround = false;

    RigidbodyComponent(GameObject* owner) : Component(owner) {}

    virtual ~RigidbodyComponent() = default;

    void AddForce(const glm::vec3 force);
    void AddImpulse(const glm::vec3& impulse);

    void Stop();
};

