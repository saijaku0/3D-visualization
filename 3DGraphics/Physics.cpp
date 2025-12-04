#include "Physics.h"
#define PHYSICS_H

bool Physics::checkCollisionAABB(const GameObject& one, const GameObject& two) {
	glm::vec3 position_one = one.transform.Position;
	glm::vec3 position_two = two.transform.Position;

	glm::vec3 scale_one = one.transform.Scale / 2.0f;
	glm::vec3 scale_two = getRotatedExtents(two);

	bool collisionX = position_one.x + scale_one.x >= position_two.x - scale_two.x && 
		position_two.x + scale_two.x >= position_one.x - scale_one.x;
	bool collisionY = position_one.y + scale_one.y >= position_two.y - scale_two.y && 
		position_two.y + scale_two.y >= position_one.y - scale_one.y;
	bool collisionZ = position_one.z + scale_one.z >= position_two.z - scale_two.z && 
		position_two.z + scale_two.z >= position_one.z - scale_one.z;

	return collisionX && collisionY && collisionZ;
}

void Physics::moveWithCollision(GameObject& obj, float dt, const std::vector<GameObject>& obstacles) {
    if (obj.isStatic) return;

    bool groundHit = false;
    obj.onGround = false;

    obj.velocity.y -= GRAVITY * dt;

    ResolveAxisCollision(obj, dt, obstacles, 0, groundHit);
    ResolveAxisCollision(obj, dt, obstacles, 2, groundHit);
    ResolveAxisCollision(obj, dt, obstacles, 1, groundHit);
    
    obj.onGround = groundHit;

    obj.velocity.x = glm::mix(obj.velocity.x, 0.0f, FRICTION * dt);
    obj.velocity.z = glm::mix(obj.velocity.z, 0.0f, FRICTION * dt);
}

glm::vec3 Physics::getRotatedExtents(const GameObject& obj) {
    float angleY = obj.transform.Rotation.y;

    if (angleY != 0.0f) {
        float normalizedAngle = std::fmod(std::abs(angleY), 360.0f);
        if (std::abs(normalizedAngle - 90.0f) < 0.1f ||
            std::abs(normalizedAngle - 270.0f) < 0.1f)
        {
            return glm::vec3(obj.transform.Scale.z / 2.0f, obj.transform.Scale.y / 2.0f, obj.transform.Scale.x / 2.0f);
        }
    }
    return obj.transform.Scale / 2.0f;
}

void Physics::ResolveAxisCollision(GameObject& obj,
    float dt,
    const std::vector<GameObject>& obstacles,
    int axis,
    bool& groundHit)
{
    float& posComponent = obj.transform.Position[axis];
    float& velComponent = obj.velocity[axis];

    float distance = velComponent * dt;
    posComponent += distance;

    for (const auto& wall : obstacles) {
        if (&obj == &wall) continue;
        if (wall.isStatic && checkCollisionAABB(obj, wall)) {
            if (axis == 1 && velComponent < 0) {
                if (std::abs(velComponent) < 2.0f) {
                    groundHit = true;
                }
            }

            if (axis == 1 && velComponent < 0) {
                groundHit = true;
            }

            posComponent -= distance;

            velComponent = 0.0f;

            break;
        }
    }
}

void Physics::moveBall(GameObject& obj, float dt, const std::vector<GameObject>& obstacles, float elasticity) {
    obj.velocity.y -= GRAVITY * dt;

    ResolveBallCollision(obj, dt, obstacles, 0, elasticity); 
    ResolveBallCollision(obj, dt, obstacles, 2, elasticity); 
    ResolveBallCollision(obj, dt, obstacles, 1, elasticity); 

    if (obj.onGround) {
        obj.velocity.x = glm::mix(obj.velocity.x, 0.0f, FRICTION * dt);
        obj.velocity.z = glm::mix(obj.velocity.z, 0.0f, FRICTION * dt);
    }
}

void Physics::ResolveBallCollision(GameObject& obj, float dt, const std::vector<GameObject>& obstacles, int axis, float elasticity) {
    float& posComponent = obj.transform.Position[axis];
    float& velComponent = obj.velocity[axis];

    float distance = velComponent * dt;
    posComponent += distance;

    for (const auto& obstacle : obstacles) {
        if (&obj == &obstacle) continue;

        if (checkCollisionAABB(obj, obstacle)) {
            posComponent -= distance;

            if (std::abs(velComponent) > 2.0f) {
                velComponent = -velComponent * elasticity; 
            }
            else {
                velComponent = 0.0f;
            }

            if (axis == 1 && distance < 0) {
                obj.onGround = true;
            }
            break;
        }
    }
}