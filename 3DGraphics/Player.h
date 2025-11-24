#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Physics.h"
#include "IMoveAble.h"
#include <GLFW/glfw3.h>
#include <vector>

class Player : public GameObject, public IMovable {
public:
    float moveSpeed;
    float jumpForce;

    glm::vec3 camFront;
    glm::vec3 camRight;

    glm::vec3 wishDir;

    Player();
    virtual ~Player() = default;

    void Update(float dt, const std::vector<GameObject>& mapObjects, glm::vec3 front, glm::vec3 right);
    void ProcessMovement(MovementDirection direction, float deltaTime) override;
    void JumpProcess();
    void UpdateCameraVectors(glm::vec3 front, glm::vec3 right);
};

#endif // !PLAYER_H