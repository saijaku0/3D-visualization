#pragma warning(disable : 4996) // Отключает предупреждение VCR102 для Visual Studio

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>	
#include <iostream>
#include <concepts>
#include <type_traits>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T>
concept ShaderParam =
	std::is_same_v<T, bool> ||
	std::is_same_v<T, int> ||
	std::is_same_v<T, float> ||
	std::is_same_v<T, glm::vec2> ||
	std::is_same_v<T, glm::vec3> ||
	std::is_same_v<T, glm::vec4> ||
	std::is_same_v<T, glm::mat2> ||
	std::is_same_v<T, glm::mat3> ||
	std::is_same_v<T, glm::mat4>;

class Shader {
	unsigned int ID;
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	
	template <ShaderParam T>
	void set(const std::string& name, const T& value) const {
		int location = glGetUniformLocation(ID, name.c_str());

		if constexpr (std::is_same_v<T, bool>) {
			glUniform1i(location, (int)value);
		}
		else if constexpr (std::is_same_v<T, int>) {
			glUniform1i(location, value);
		}
		else if constexpr (std::is_same_v<T, float>) {
			glUniform1f(location, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec2>) {
			glUniform2fv(location, 1, &value[0]);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>) {
			glUniform3fv(location, 1, &value[0]);
		}
		else if constexpr (std::is_same_v<T, glm::vec4>) {
			glUniform4fv(location, 1, &value[0]);
		}
		else if constexpr (std::is_same_v<T, glm::mat2>) {
			glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
		}
		else if constexpr (std::is_same_v<T, glm::mat3>) {
			glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
		}
		else if constexpr (std::is_same_v<T, glm::mat4>) {
			glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]); 
		}
	}

	void use() const;
	void setVec3(const std::string& name, float x, float y, float z) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // !1
