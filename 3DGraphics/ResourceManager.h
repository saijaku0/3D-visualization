#pragma once
#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"

class ResourceManager {
public:
	static std::map<std::string, std::shared_ptr<Shader>> Shaders;

	static std::shared_ptr<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

	static std::shared_ptr<Shader> GetShader(std::string name);

	//static unsigned int LoadTexture(const char* file, std::string name);
	//static unsigned int GetTexture(std::string name);

	static void Clear();
private:
	ResourceManager() {}
};

