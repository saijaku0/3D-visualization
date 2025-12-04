#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <cmath>
#include <glm/glm.hpp>
#include "GameObject.h" 

class Physics {
    static constexpr float GRAVITY = 20.0f;
    static constexpr float FRICTION = 10.0f;

public:
    static bool checkCollisionAABB(const GameObject& one, const GameObject& two);

    static void moveWithCollision(GameObject& obj, float dt, const std::vector<GameObject>& obstacles);

    static void moveBall(GameObject& obj, float dt, const std::vector<GameObject>& obstacles, float elasticity = 0.8f);
private:
    static glm::vec3 getRotatedExtents(const GameObject& obj);

    static void ResolveBallCollision(GameObject& obj, float dt, const std::vector<GameObject>& obstacles, int axis, float elasticity);

    static void ResolveAxisCollision(GameObject& obj,
        float dt,
        const std::vector<GameObject>& obstacles,
        int axis,
        bool& groundHit);
};

#endif // !PHYSICS_H