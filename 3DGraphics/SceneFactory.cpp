#include "SceneFactory.h"

void SceneFactory::CreateResources(std::shared_ptr<Mesh>& cubeMesh, std::shared_ptr<Mesh>& pyramidMesh) {
    cubeMesh = std::shared_ptr<Mesh>(GeometryGenerator::CreateCube());
    pyramidMesh = std::shared_ptr<Mesh>(GeometryGenerator::CreatePyramid());
}

void SceneFactory::LoadDefaultScene(std::vector<GameObject>& objects, std::shared_ptr<Mesh> cubeMesh, std::shared_ptr<Mesh> pyramidMesh) {
    // --- Пол ---
    GameObject floor = CreateObject(
        cubeMesh,
        glm::vec3(0.0f, -2.0f, 0.0f),       
        glm::vec3(15.0f, 0.1f, 15.0f),      
        glm::vec3(0.6f, 0.6f, 0.6f),        
        glm::vec3(0.0f, 0.0f, 0.0f)         
    );
    floor.isStatic = true;
    objects.push_back(floor);

    // --- Стена (Задняя) ---
    GameObject wallBack = CreateObject(
        cubeMesh,
        glm::vec3(0.0f, -1.0f, -7.0f),
        glm::vec3(0.5f, 2.5f, 15.0f),
        glm::vec3(0.2f, 0.8f, 0.2f),
        glm::vec3(0.0f, 90.0f, 0.0f) 
    );
    wallBack.isStatic = true;
    objects.push_back(wallBack);

    // --- Стена (Передняя) ---
    GameObject wallFront = CreateObject(
        cubeMesh,
        glm::vec3(0.0f, -1.0f, 7.0f),
        glm::vec3(0.5f, 2.5f, 15.0f),
        glm::vec3(0.2f, 0.8f, 0.2f),
        glm::vec3(0.0f, 90.0f, 0.0f)
    );
    wallFront.isStatic = true;
    objects.push_back(wallFront);

    // --- Стена (Правая) ---
    GameObject wallRight = CreateObject(
        cubeMesh,
        glm::vec3(7.0f, -1.0f, 0.0f),
        glm::vec3(0.5f, 2.5f, 15.0f),
        glm::vec3(0.2f, 0.8f, 0.2f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    wallRight.isStatic = true;
    objects.push_back(wallRight);

    // --- Стена (Левая) ---
    GameObject wallLeft = CreateObject(
        cubeMesh,
        glm::vec3(-7.0f, -1.0f, 0.0f),
        glm::vec3(0.5f, 2.5f, 15.0f),
        glm::vec3(0.2f, 0.8f, 0.2f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    wallLeft.isStatic = true;
    objects.push_back(wallLeft);

    // --- Пирамида ---
    GameObject pyramid = CreateObject(
        pyramidMesh,
        glm::vec3(-2.0f, -2.0f, 0.0f),
        glm::vec3(1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f)
    );
    pyramid.isStatic = true;
    objects.push_back(pyramid);
}

GameObject SceneFactory::CreateObject(std::shared_ptr<Mesh> mesh, glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 rotation) {
    GameObject obj;

    obj.transform.Position = pos;
    obj.transform.Scale = scale;
    obj.transform.Rotation = rotation;

    obj.color = color;
    obj.mesh = mesh; 
    // obj.rotationSpeed = rotSpeed; // Пока убрали, так как в Transform этого нет, но можно добавить логику позже

    return obj;
}