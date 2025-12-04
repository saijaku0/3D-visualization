#pragma once
#ifndef PLAYER_H
#define PLAYER_H 

#include "GameObject.h"
#include <GLFW/glfw3.h> 
#include <vector>
#include <glm/glm.hpp>

class Physics;

class Player : public GameObject {
public:
    float moveSpeed;
    float jumpForce;

    glm::vec3 camFront;
    glm::vec3 camRight;

    glm::vec3 wishDir;

    Player();
    virtual ~Player() = default;

    void ProcessInput(GLFWwindow* window, glm::vec3 front, glm::vec3 right);

    void Update(float dt, const std::vector<GameObject>& mapObjects);

private:
    void Jump();
};

#endif // !PLAYER_H