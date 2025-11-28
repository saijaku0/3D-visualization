#pragma once
#ifndef SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <map>

#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "Player.h"
#include "GeometryGenerator.h"
#include "IMoveAble.h"
#include "InputManager.h"
#include "GameManager.h"
#include "LightingSystem.h"
#include "Renderer.h"
#include "SceneFactory.h"
#include "AttachedCamera.h"
#include "Skybox.h"

class Scene {
	Mesh* cubeMesh;
	Mesh* pyramidMesh;

	std::vector<GameObject> gameObjects;
	InputManager inputManager;
	IMovable* currentController;
	Player playerObj;
	Renderer renderer;
	GameManager gameManager;
	FreeCamera* devCamera;
	AttachedCamera* playerCamera;
	Camera* activeCamera;
	LightingSystem lightingSystem;
	SceneFactory sceneFactory;
	Skybox* skybox;

	float gameTime;
	glm::vec3 pointLightPos;
public:
	Scene(int width, int height);
	~Scene();

	void Init();
	void ProcessInput(GLFWwindow* window, float deltaTime);
	void ProcessMouseMovement(double xpos, double ypos, bool enableRotation);
	void Update(float deltaTime);
	void Draw(Shader& shader, int scrWidth, int scrHeight);
	GameManager& GetGameManager() {
		return gameManager;
	}
private:
	bool updateCursorState(GLFWwindow* window);
	void handleMovementInput(GLFWwindow* window, float deltaTime);
};

#endif // !SCENE_H

