#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory> 

class Mesh;
class Shader;

struct Transform {
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f); 
    glm::vec3 Scale = glm::vec3(1.0f);

    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, Scale);
        return model;
    }
};

class GameObject {
public:
    Transform transform; 

    std::shared_ptr<Mesh> mesh;

    glm::vec3 color;
    glm::vec3 velocity;

    bool isStatic;
    bool onGround;

public:
    GameObject()
        : color(1.0f), velocity(0.0f), isStatic(false), onGround(false)
    {
    }

    virtual ~GameObject() = default;
    
    void Draw(const Shader& shader) const;

    void UpdatePhysics(float deltaTime) {
        if (!isStatic) {
            transform.Position += velocity * deltaTime;
        }
    }
};

#endif