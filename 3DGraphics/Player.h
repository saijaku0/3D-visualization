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

    Player() : GameObject() {
        moveSpeed = 7.0f;
        jumpForce = 8.0f;
        isStatic = false;
        scale = glm::vec3(0.5f, 1.8f, 0.5f);
        camFront = glm::vec3(0.0f, 0.0f, -1.0f);
        camRight = glm::vec3(1.0f, 0.0f, 0.0f);
        wishDir = glm::vec3(0.0f);
    }

    void Update(float dt, const std::vector<GameObject>& mapObjects, glm::vec3 front, glm::vec3 right) {
        camFront = front;
        camRight = right;

        if (glm::length(wishDir) > 0.0f) {
            wishDir = glm::normalize(wishDir);
            velocity.x = wishDir.x * moveSpeed;
            velocity.z = wishDir.z * moveSpeed;
        }
        else {
            velocity.x = 0.0f;
            velocity.z = 0.0f;
        }

        wishDir = glm::vec3(0.0f);

        Physics::moveWithCollision(*this, dt, mapObjects);
    }

    void ProcessMovement(MovementDirection direction, float deltaTime) override {
        glm::vec3 front = glm::normalize(glm::vec3(camFront.x, 0.0f, camFront.z));
        glm::vec3 right = glm::normalize(glm::vec3(camRight.x, 0.0f, camRight.z));

        if (direction == MOVE_FORWARD)  wishDir += front;
        if (direction == MOVE_BACKWARD) wishDir -= front;
        if (direction == MOVE_LEFT)     wishDir -= right;
        if (direction == MOVE_RIGHT)    wishDir += right;

        if (direction == MOVE_JUMP) JumpProcess();
    }

    void JumpProcess() {
        if (std::abs(velocity.y) < 0.01f && this->onGround)
            velocity.y = jumpForce;
    }

    void UpdateCameraVectors(glm::vec3 front, glm::vec3 right) {
        camFront = front;
        camFront.y = 0.0f;

        if (glm::length(camFront) > 0.0001f) {
            camFront = glm::normalize(camFront);
        }
        else {
            camFront = glm::vec3(0.0f, 0.0f, -1.0f); 
        }

        camRight = right;
        camRight.y = 0.0f;
        camRight = glm::normalize(camRight);
    }
};

#endif // !PLAYER_H