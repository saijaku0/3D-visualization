#pragma once
#ifndef SKYBOX_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Shader.h" 
#include "Camera.h" 
#include "stb_image.h"

class Skybox {
private:
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int textureID;
    Shader* skyboxShader; 

public:
    Skybox();
    ~Skybox();

    void LoadCubemap(std::vector<std::string> faces);
    void Draw(const glm::mat4& view, const glm::mat4& projection);
};

#endif // !SKYBOX_H