#include "Scene.h"

Scene::Scene(int width, int height) : 
	gameManager(width, height), 
	lightingSystem(glm::vec3(0.0f, 1.0f, 0.0f)), 
	renderer(),
	gameTime(0.0f),
	pointLightPos(0.0f, 1.0f, 0.0f),
	cubeMesh(nullptr),
	pyramidMesh(nullptr),
	devCamera(nullptr),
	playerCamera(nullptr),
	activeCamera(nullptr),
	currentController(nullptr)
{
	Init();
}

Scene::~Scene() {
	delete cubeMesh;
	delete pyramidMesh;
	delete devCamera;
	delete playerCamera;
}

void Scene::Init() {
	SceneFactory::CreateResources(cubeMesh, pyramidMesh);
	SceneFactory::LoadDefaultScene(gameObjects, cubeMesh, pyramidMesh);

	playerObj.moveSpeed = 10.0f;
	playerObj.position = glm::vec3(0.0f, 0.0f, 5.0f);
	playerObj.scale = glm::vec3(0.5f);
	playerObj.color = glm::vec3(1.0f, 0.0f, 0.0f);
	playerObj.mesh = cubeMesh;
	playerObj.isStatic = false;

	devCamera = new FreeCamera(glm::vec3(0.0f, 5.0f, 10.0f));
	playerCamera = new AttachedCamera(&playerObj, glm::vec3(0.0f, 0.6f, 0.0f));

	activeCamera = devCamera;
	currentController = devCamera;

	inputManager.BindKey(GLFW_KEY_W, MOVE_FORWARD);
	inputManager.BindKey(GLFW_KEY_S, MOVE_BACKWARD);
	inputManager.BindKey(GLFW_KEY_A, MOVE_LEFT);
	inputManager.BindKey(GLFW_KEY_D, MOVE_RIGHT);
	inputManager.BindKey(GLFW_KEY_SPACE, MOVE_JUMP);
}

void Scene::ProcessInput(GLFWwindow* window, float deltaTime) {
	gameManager.ProcessModeSwitch(window, devCamera, playerCamera, &playerObj, &activeCamera, &currentController);

	bool cursorEnabled = gameManager.IsMouseRotationActive(window);

	if (cursorEnabled)
		handleMovementInput(window, deltaTime);
}

void Scene::Draw(Shader& shader, int scrWidth, int scrHeight) {
	renderer.Clear();

	renderer.DrawScene(
		shader,
		activeCamera,
		lightingSystem,
		gameObjects,
		cubeMesh, 
		gameTime,
		scrWidth, scrHeight
	);

	if (!gameManager.GetGameMode()) {

		shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);
		playerObj.draw(shader, 0);

		GameObject headGizmo;
		headGizmo.position = playerCamera->GetPosition();
		headGizmo.scale = glm::vec3(0.2f);
		headGizmo.color = glm::vec3(0.0f, 0.0f, 1.0f);
		headGizmo.mesh = cubeMesh;
		headGizmo.draw(shader, 0);

		shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	}
}

void Scene::Update(float deltaTime) {
	activeCamera->Update(deltaTime);

	if (!gameManager.GetGameMode()) return;

	gameTime += deltaTime;

	lightingSystem.Update(deltaTime);

	playerObj.Update(deltaTime, gameObjects, activeCamera->GetFront(), activeCamera->GetRight());
}

void Scene::ProcessMouseMovement(double xpos, double ypos, bool enableRotation) {
	if (!enableRotation) {
		gameManager.GetLastX() = xpos;
		gameManager.GetLastY() = ypos;
		return;
	}

	if (gameManager.GetFirstMouse()) {
		gameManager.GetLastX() = xpos;
		gameManager.GetLastY() = ypos;
		gameManager.GetFirstMouse() = false;
	}

	float xoffset = (float)xpos - gameManager.GetLastX();
	float yoffset = gameManager.GetLastY() - (float)ypos; 

	gameManager.GetLastX() = xpos;
	gameManager.GetLastY() = ypos;

	activeCamera->ProcessMouseMovement(xoffset, yoffset);
}

void Scene::handleMovementInput(GLFWwindow* window, float deltaTime) {
	if (!currentController) return;

	if (gameManager.GetGameMode()) {
		playerObj.UpdateCameraVectors(activeCamera->GetFront(), activeCamera->GetRight());
	}

	inputManager.HandleInput(window, *currentController, deltaTime);
}

bool Scene::updateCursorState(GLFWwindow* window) {
	if (gameManager.GetGameMode()) return true;

	bool rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	if (rightClick) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return true;
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		gameManager.GetFirstMouse() = true;
		return false;
	}
}
