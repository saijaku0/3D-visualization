#pragma once
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>

class GameObject;
class PhysicsWorld; 

class SceneFactory {
public:
    static void LoadDefaultScene(
        std::vector<std::unique_ptr<GameObject>>& objects,
        PhysicsWorld* physicsWorld
    );

private:
    static std::unique_ptr<GameObject> CreateBox(
        const std::string& meshName,
        glm::vec3 pos,
        glm::vec3 scale,
        glm::vec3 rotation, // В градусах (Euler Angles)
        bool isStatic,
        PhysicsWorld* physicsWorld
    );
};