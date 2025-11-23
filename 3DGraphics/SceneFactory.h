#pragma once
#include "GameObject.h"
#include "GeometryGenerator.h"

class SceneFactory {
public:
    static void CreateResources(Mesh*& cubeMesh, Mesh*& pyramidMesh) {
        cubeMesh = GeometryGenerator::CreateCube();
        pyramidMesh = GeometryGenerator::CreatePyramid();
    }

    static void LoadDefaultScene(std::vector<GameObject>& objects, Mesh* cubeMesh, Mesh* pyramidMesh) {
        // Пол
        GameObject floor;
        floor.position = glm::vec3(0.0f, -2.0f, 0.0f);
        floor.scale = glm::vec3(15.0f, 0.1f, 15.0f);
        floor.mesh = cubeMesh;
        floor.color = glm::vec3(0.6f, 0.6f, 0.6f);
        objects.push_back(floor);

        // Стена
        GameObject wall;
        wall.position = glm::vec3(0.0f, 1.0f, -2.5f);
        wall.scale = glm::vec3(1.0f, 5.0f, 4.0f);
        wall.rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        wall.color = glm::vec3(0.2f, 0.8f, 0.2f);
        wall.angle = 90.0f;
        wall.mesh = cubeMesh;
        objects.push_back(wall);

        // Вентилятор
        GameObject fan;
        fan.position = glm::vec3(2.0f, 0.0f, 0.0f);
        fan.scale = glm::vec3(3.0f, 0.2f, 0.2f);
        fan.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
        fan.rotationSpeed = 200.0f;
        fan.mesh = cubeMesh;
        objects.push_back(fan);

        // Пирамида
        GameObject pyramid;
        pyramid.position = glm::vec3(-2.0f, -1.0f, 0.0f);
        pyramid.color = glm::vec3(1.0f, 1.0f, 1.0f);
        pyramid.mesh = pyramidMesh;
        objects.push_back(pyramid);
    }

    GameObject CreateObject(Mesh* mesh, glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float angle, float rotSpeed, glm::vec3 rotAxis) {
        GameObject obj;
        obj.mesh = mesh;
        obj.position = pos;
        obj.scale = scale;
        obj.color = color;
        obj.angle = angle;
        obj.rotationSpeed = rotSpeed;
        obj.rotationAxis = rotAxis;
        return obj;
    }
};