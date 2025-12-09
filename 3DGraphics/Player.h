#pragma once
#ifndef PLAYER_H
#define PLAYER_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <vector>
#include "Core/GameObject.h"

class InputManager;
class Camera;

class Player : public GameObject {
public:
    Player(InputManager* input, Camera* camera);
    virtual ~Player() = default;

};

#endif // !PLAYER_H