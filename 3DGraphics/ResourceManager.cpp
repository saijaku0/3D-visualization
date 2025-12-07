#include "ResourceManager.h"

std::map<std::string, std::shared_ptr<Shader>> ResourceManager::Shaders;

std::shared_ptr<Shader> ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
    Shaders[name] = std::make_shared<Shader>(vShaderFile, fShaderFile);

    return Shaders[name];
}

std::shared_ptr<Shader> ResourceManager::GetShader(std::string name)
{
    if (Shaders.find(name) != Shaders.end())
        return Shaders[name];

    std::cerr << "ERROR::RESOURCEMANAGER::SHADER_NOT_FOUND: " << name << std::endl;
    return nullptr;
}

void ResourceManager::Clear()
{
    Shaders.clear();
}