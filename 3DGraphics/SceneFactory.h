#pragma once
#include "GameObject.h"
#include "GeometryGenerator.h"

class SceneFactory {
public:
    static void CreateResources(Mesh*& cubeMesh, Mesh*& pyramidMesh);

    static void LoadDefaultScene(std::vector<GameObject>& objects, Mesh* cubeMesh, Mesh* pyramidMesh);

    GameObject CreateObject(
        Mesh* mesh, 
        glm::vec3 pos, 
        glm::vec3 scale, 
        glm::vec3 color, 
        float angle, 
        float rotSpeed, 
        glm::vec3 rotAxis
    );
};