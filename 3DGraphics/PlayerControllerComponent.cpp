#include "PlayerControllerComponent.h"

void PlayerControllerComponent::Update(float dt) {
    auto rb = GetOwner()->GetComponent<RigidbodyComponent>();
    if (!rb) return;

    glm::vec3 forward = m_camera->GetFront();
    glm::vec3 right = m_camera->GetRight();

    forward.y = 0;
    right.y = 0;
    forward = glm::normalize(forward);
    right = glm::normalize(right);

    glm::vec3 moveDir = glm::vec3(0.0f);

    // 3. Обработка ввода
    if (m_input->GetButton(GameAction::MoveForward))  moveDir += forward;
    if (m_input->GetButton(GameAction::MoveBackward)) moveDir -= forward;
    if (m_input->GetButton(GameAction::MoveRight))    moveDir += right;
    if (m_input->GetButton(GameAction::MoveLeft))     moveDir -= right;

    if (glm::length(moveDir) > 0.1f) {
        moveDir = glm::normalize(moveDir);

        rb->velocity.x = moveDir.x * m_speed;
        rb->velocity.z = moveDir.z * m_speed;
    }
    else {
        rb->velocity.x = 0.0f;
        rb->velocity.z = 0.0f;
    }

    if (m_input->GetButton(GameAction::Jump) && rb->onGround) {
        rb->velocity.y = m_jumpForce;
        rb->onGround = false;
    }
}