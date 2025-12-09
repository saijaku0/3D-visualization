#pragma once
#include "InputManager.h"
#include "Core/Component.h"
#include "Physics/RigidbodyComponent.h"
#include "Camera/Camera.h" 
#include "Core/GameObject.h"

class PlayerControllerComponent : public Component {
    InputManager* m_input;
    Camera* m_camera;

    float m_speed = 5.0f;
    float m_jumpForce = 400.0f;
public:
    PlayerControllerComponent(GameObject* owner, InputManager* input, Camera* cam)
        : Component(owner), m_input(input), m_camera(cam) {
    }

    void Update(float dt) override;
};