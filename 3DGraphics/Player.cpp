#include "Player.h"
#include "Physics.h"
#include <iostream>
#include <cmath>

Player::Player() : GameObject() {
    moveSpeed = 7.0f;
    jumpForce = 8.0f;
    isStatic = false;

    transform.Scale = glm::vec3(0.5f, 1.8f, 0.5f);

    camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    camRight = glm::vec3(1.0f, 0.0f, 0.0f);
    wishDir = glm::vec3(0.0f);

    color = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Player::Update(float dt, const std::vector<GameObject>& mapObjects) {
    glm::vec3 wishVelocity = glm::vec3(0.0f);

    if (glm::length(wishDir) > 0.0f) {
        wishDir = glm::normalize(wishDir);
        wishVelocity.x = wishDir.x * moveSpeed;
        wishVelocity.z = wishDir.z * moveSpeed;
    }

    if (onGround) {
        velocity.x = wishVelocity.x;
        velocity.z = wishVelocity.z;
    }
    else if (glm::length(wishVelocity) > 0.0f) {
        velocity.x = glm::mix(velocity.x, wishVelocity.x, 0.1f);
        velocity.z = glm::mix(velocity.z, wishVelocity.z, 0.1f);
    }

    wishDir = glm::vec3(0.0f);

    Physics::moveWithCollision(*this, dt, mapObjects);
}

void Player::ProcessInput(GLFWwindow* window, glm::vec3 front, glm::vec3 right) {
    camFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
    camRight = glm::normalize(glm::vec3(right.x, 0.0f, right.z));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        wishDir += camFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        wishDir -= camFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        wishDir -= camRight;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        wishDir += camRight;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Jump();
}

void Player::Jump() {
    if (onGround && std::abs(velocity.y) < 0.1f) {
        velocity.y = jumpForce;
        onGround = false; 
    }
}