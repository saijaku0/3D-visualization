#pragma once
#include "Component.h"
#include "InputManager.h"
#include "RigidbodyComponent.h"
#include "Camera.h" 
#include "GameObject.h"

class PlayerControllerComponent : public Component {
    InputManager* m_input;
    Camera* m_camera;

    float m_speed = 5.0f;
    float m_jumpForce = 5.0f;
public:
    PlayerControllerComponent(GameObject* owner, InputManager* input, Camera* cam)
        : Component(owner), m_input(input), m_camera(cam) {
    }

    void Update(float dt) override;
};