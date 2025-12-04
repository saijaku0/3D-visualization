#pragma warning(disable : 4996) 

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>	
#include <iostream>
#include <unordered_map> 
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
private:
	unsigned int ID;
	mutable std::unordered_map<std::string, int> uniformCache;

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	~Shader() {
		glDeleteProgram(ID);
	}

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept : ID(other.ID) {
		other.ID = 0; 
	}
	Shader& operator=(Shader&& other) noexcept {
		if (this != &other) {
			glDeleteProgram(ID);
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

	void use() const;

	template <ShaderParam T>
	void set(const std::string& name, const T& value) const {
		int location = getUniformLocation(name); 

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

	void setMat4(const std::string& name, const glm::mat4& mat) const {
		set(name, mat);
	}

	void setVec3(const std::string& name, const glm::vec3& val) const {
		set(name, val);
	}

	void setVec3(const std::string& name, float x, float y, float z) const {
		set(name, glm::vec3(x, y, z));
	}

	void setFloat(const std::string& name, float val) const {
		set(name, val);
	}

	void setInt(const std::string& name, int val) const {
		set(name, val);
	}

private:
	void checkCompileErrors(unsigned int shader, std::string type);

	int getUniformLocation(const std::string& name) const {
		if (uniformCache.find(name) != uniformCache.end())
			return uniformCache[name];

		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1) {
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		}

		uniformCache[name] = location;
		return location;
	}
};

#endif