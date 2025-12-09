#include "FreeCamera.h"

void FreeCamera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = m_MovementSpeed * deltaTime;

    if (direction == CameraMovement::Forward)
        m_Position += m_Front * velocity;
    if (direction == CameraMovement::Backward)
        m_Position -= m_Front * velocity;
    if (direction == CameraMovement::Left)
        m_Position -= m_Right * velocity;
    if (direction == CameraMovement::Right)
        m_Position += m_Right * velocity;

    // ≈сли хочешь насто€щий "полет" (как в редакторе Unity/Unreal):
    if (direction == CameraMovement::Up)
        m_Position += m_Up * velocity;
    if (direction == CameraMovement::Down)
        m_Position -= m_Up * velocity;
}