#pragma once
#include "Scene.h" 

class EditorManager {
public:
    void Init(GLFWwindow* window);

    void Draw(Scene* scene);

    void Shutdown();

private:
    GameObject* m_selectedObject = nullptr;
};