#pragma once
#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Physics.h"

class Ball : public GameObject {
public:
    float elasticity; 

    Ball() : elasticity(0.8f) {
        transform.Scale = glm::vec3(0.5f); 
        color = glm::vec3(0.0f, 0.0f, 1.0f); 
    }

    void Update(float dt, const std::vector<GameObject>& obstacles) {
        Physics::moveBall(*this, dt, obstacles, elasticity);

        if (transform.Position.y < -10.0f) {
            transform.Position = glm::vec3(0.0f, 5.0f, 0.0f);
            velocity = glm::vec3(0.0f);
        }
    }
};

#endif