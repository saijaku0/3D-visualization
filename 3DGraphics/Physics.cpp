#include "Physics.h"
#define PHYSICS_H

bool Physics::checkCollisionAABB(const GameObject& one, const GameObject& two) {
	glm::vec3 position_one = one.position;
	glm::vec3 position_two = two.position;

	glm::vec3 scale_one = one.scale / 2.0f;
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
    if (obj.angle != 0.0f) {
        float normalizedAngle = fmod(obj.angle, 360.0f);
        if (std::abs(normalizedAngle - 90.0f) < 0.1f ||
            std::abs(normalizedAngle - 270.0f) < 0.1f)
        {
            return glm::vec3(obj.scale.z / 2.0f, obj.scale.y / 2.0f, obj.scale.x / 2.0f);
        }
    }
    return obj.scale / 2.0f;
}

void Physics::ResolveAxisCollision(GameObject& obj,
    float dt,
    const std::vector<GameObject>& obstacles,
    int axis,
    bool& groundHit)
{
    float& posComponent = obj.position[axis];
    float& velComponent = obj.velocity[axis];

    float distance = velComponent * dt;
    posComponent += distance;

    for (const auto& wall : obstacles) {
        if (&obj == &wall) continue;
        if (wall.isStatic && checkCollisionAABB(obj, wall)) {

            if (axis == 1 && velComponent < 0) {
                groundHit = true;
            }

            posComponent -= distance;

            velComponent = 0.0f;

            break;
        }
    }
}