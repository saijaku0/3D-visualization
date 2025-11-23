#pragma warning(disable : 4996) // Отключает предупреждение VCR102 для Visual Studio

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>	
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
	unsigned int ID;
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	
	void use() const;

	void setBool(const std::string& name, bool value) const;

	void setFloat(const std::string& name, float value) const;

	void setMat4(const std::string& name, const glm::mat4& mat) const;

	void setVec3(const std::string& name, const glm::vec3& vec) const;

	void setVec3(const std::string& name, float x, float y, float z) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // !1
