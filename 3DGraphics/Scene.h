#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <map>

#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "GeometryGenerator.h"

class Scene {
public:
	Mesh* cubeMesh;
	Mesh* pyramidMesh;

	std::vector<GameObject> gameObjects;
	std::map<int, Camera_Movement> keyBindings;
	GameObject playerObj;

	Camera camera;
	bool isGameMode;
	bool firstMouse;
	bool escKeyPressed;
	float lastX, lastY;
	float gameTime;

	glm::vec3 pointLightPos;

	Scene(int width, int height) :
		camera(glm::vec3(0.0f, 2.0f, 5.0f)),
		pointLightPos(1.0f, 1.0f, 1.0f),
		isGameMode(false),
		firstMouse(true),
		lastX(width / 2.0f),
		lastY(height / 2.0f),
		gameTime(0.0f),
		escKeyPressed(false)
	{
		cubeMesh = GeometryGenerator::CreateCube();
		pyramidMesh = GeometryGenerator::CreatePyramid();
		keyBindings[GLFW_KEY_W] = FORWARD;
		keyBindings[GLFW_KEY_S] = BACKWARD;
		keyBindings[GLFW_KEY_A] = LEFT;
		keyBindings[GLFW_KEY_D] = RIGHT;
	}

	~Scene() {
		delete cubeMesh;
		delete pyramidMesh;
	}

	void Init() {
		GameObject floor;
		floor.position = glm::vec3(0.0f, -2.0f, 0.0f);
		floor.scale = glm::vec3(10.0f, 0.1f, 5.0f);
		floor.mesh = cubeMesh;
		floor.color = glm::vec3(0.6f, 0.6f, 0.6f);
		gameObjects.push_back(floor);

		GameObject wall;
		wall.position = glm::vec3(0.0f, 1.0f, -2.5f);
		wall.scale = glm::vec3(1.0f, 5.0f, 4.0f);
		wall.rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		wall.color = glm::vec3(0.2f, 0.8f, 0.2f);
		wall.angle = 90.0f;
		wall.mesh = cubeMesh;
		gameObjects.push_back(wall);

		GameObject fan;
		fan.position = glm::vec3(2.0f, 0.0f, 0.0f);
		fan.scale = glm::vec3(3.0f, 0.2f, 0.2f);
		fan.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		fan.rotationSpeed = 200.0f;
		fan.mesh = cubeMesh;
		gameObjects.push_back(fan);

		playerObj.position = glm::vec3(0.0f, 0.0f, 5.0f); 
		playerObj.scale = glm::vec3(0.5f);                
		playerObj.color = glm::vec3(1.0f, 0.0f, 0.0f);    
		playerObj.mesh = cubeMesh;

		GameObject pyramid;
		pyramid.position = glm::vec3(-2.0f, -1.0f, 0.0f);
		pyramid.color = glm::vec3(1.0f, 1.0f, 1.0f);
		pyramid.mesh = pyramidMesh;
		gameObjects.push_back(pyramid);
	}

	void ProcessInput(GLFWwindow* window, float deltaTime) {
		hendleModeSwitching(window);

		bool cursorEnabled = updateCursorState(window);

		if (cursorEnabled) 
			handleMovementInput(window, deltaTime);
	}

	void ProcessMouseMovement(double xpos, double ypos, bool enableRotation) {
		if (!enableRotation) {
			lastX = xpos;
			lastY = ypos;
			return;
		}

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		camera.processMouseMovement(xoffset, yoffset);
	}

	void Update(float deltaTime) {
		if (!isGameMode) return;

		gameTime += deltaTime;

		float lightX = sin(gameTime) * 2.0f;
		float lightZ = cos(gameTime) * 2.0f;
		pointLightPos = glm::vec3(lightX, 1.0f, lightZ);
	}

	void Draw(Shader& shader, int scrWidth, int scrHeight) {
		shader.use();

		if (scrHeight == 0) scrHeight = 1;
		float aspectRatio = (float)scrWidth / (float)scrHeight;
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setVec3("viewPos", camera.getPosition());

		shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		shader.setVec3("pointLight.position", pointLightPos);
		shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
		shader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
		shader.setFloat("pointLight.constant", 1.0f);
		shader.setFloat("pointLight.linear", 0.09f);
		shader.setFloat("pointLight.quadratic", 0.032f);

		GameObject gizmoLamp;
		gizmoLamp.position = pointLightPos;
		gizmoLamp.scale = glm::vec3(0.2f);
		gizmoLamp.color = glm::vec3(1.0f, 1.0f, 0.0f);
		gizmoLamp.mesh = cubeMesh;
		gizmoLamp.draw(shader, 0);

		for (auto& obj : gameObjects) {
			obj.draw(shader, gameTime);
		}

		if (!isGameMode) {
			shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);

			playerObj.draw(shader, 0);

			shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
		}
	}
private:
	void switchToDeveloperMode(GLFWwindow* window) {
		if (escKeyPressed) {
			return;
		}

		if (isGameMode) {
			isGameMode = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			playerObj.position = camera.getPosition();

			std::cout << "DEVELOPER MODE" << std::endl;
		}
		else {
			glfwSetWindowShouldClose(window, true);
		}

		escKeyPressed = true;
	}

	void switchToGameMode(GLFWwindow* window) {
		if (!isGameMode) {
			isGameMode = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
			camera.setPosition(playerObj.position);
			std::cout << "GAME MODE" << std::endl;
		}
	}

	void hendleModeSwitching(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !isGameMode) {
			switchToGameMode(window);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			switchToDeveloperMode(window);
		}
		else {
			escKeyPressed = false;
		}
	}

	bool updateCursorState(GLFWwindow* window) {
		if(isGameMode) return true;

		bool rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

		if(rightClick) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return true;
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstMouse = true;
			return false;
		}
	}

	void handleMovementInput(GLFWwindow* window, float deltaTime) {
		for (auto const& [key, direction] : keyBindings) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				camera.processKeyboard(direction, deltaTime);
			}
		}
	}
};

#endif // !SCENE_H

