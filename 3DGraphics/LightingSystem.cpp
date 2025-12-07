#include "LightingSystem.h"

void LightingSystem::AddPointLight(const glm::vec3& pos, const glm::vec3& color) {
	PointLight light;

	light.position = pos;
	light.diffuse = color;

	light.ambient = color * 0.1f;
	light.specular = glm::vec3(1.0f);


	light.constant = 1.0f;
	light.linear = 0.09f;
	light.quadratic = 0.032f;

	pointLights.push_back(light);
}

void LightingSystem::ApplyUniforms(Shader& shader) const {
	shader.setVec3("dirLight.direction", dirLight.direction);
	shader.setVec3("dirLight.ambient", dirLight.ambient);
	shader.setVec3("dirLight.diffuse", dirLight.diffuse);
	shader.setVec3("dirLight.specular", dirLight.specular);

	for (size_t i = 0; i < pointLights.size(); i++) {
		std::string baseName = "pointLights[" + std::to_string(i) + "]";

		shader.setVec3(baseName + ".position", pointLights[i].position);
		shader.setVec3(baseName + ".ambient", pointLights[i].ambient);
		shader.setVec3(baseName + ".diffuse", pointLights[i].diffuse);
		shader.setVec3(baseName + ".specular", pointLights[i].specular);

		shader.setFloat(baseName + ".constant", pointLights[i].constant);
		shader.setFloat(baseName + ".linear", pointLights[i].linear);
		shader.setFloat(baseName + ".quadratic", pointLights[i].quadratic);
	}
}