#pragma once
#ifndef SKYBOX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Shader.h" 
#include "Camera.h" 
#include "ResourceManager.h"
#include "stb_image.h"

class Skybox {
private:
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int textureID;
    std::shared_ptr<Shader> skyboxShader;

public:
    Skybox();
    ~Skybox();

    void LoadCubemap(std::vector<std::string>& faces);
    void Draw(const glm::mat4& view, const glm::mat4& projection);
};

#endif // !SKYBOX_H