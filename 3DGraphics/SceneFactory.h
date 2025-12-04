#pragma once
#include <vector>
#include <memory> 
#include "GameObject.h"
#include "GeometryGenerator.h"

class SceneFactory {
public:
    static void CreateResources(std::shared_ptr<Mesh>& cubeMesh, std::shared_ptr<Mesh>& pyramidMesh);

    static void LoadDefaultScene(std::vector<GameObject>& objects, std::shared_ptr<Mesh> cubeMesh, std::shared_ptr<Mesh> pyramidMesh);

    static GameObject CreateObject(
        std::shared_ptr<Mesh> mesh,
        glm::vec3 pos,
        glm::vec3 scale,
        glm::vec3 color,
        glm::vec3 rotation 
    );
};