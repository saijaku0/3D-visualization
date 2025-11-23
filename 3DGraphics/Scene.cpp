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
	//gameObjects.push_back(CreateObject(cubeMesh, glm::vec3(0, -2, 0), glm::vec3(15, 0.1, 15), glm::vec3(0.6)));
	//gameObjects.push_back(CreateObject(cubeMesh, glm::vec3(0, -2, -2.5), glm::vec3(4, 5, 1), glm::vec3(0.2, 0.8, 0.2), 90.0f));
	//gameObjects.push_back(CreateObject(cubeMesh, glm::vec3(2, 0, 0), glm::vec3(3, 0.2, 0.2), glm::vec3(1), 0.0f, 200.0f, glm::vec3(0, 0, 1)));
	//gameObjects.push_back(CreateObject(pyramidMesh, glm::vec3(-2, -2, 0), glm::vec3(2), glm::vec3(1)));
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

	if (!gameManager.isGameMode) {

		shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);
		playerObj.draw(shader, 0);

		GameObject headGizmo;
		headGizmo.position = playerCamera->position;
		headGizmo.scale = glm::vec3(0.2f);
		headGizmo.color = glm::vec3(0.0f, 0.0f, 1.0f);
		headGizmo.mesh = cubeMesh;
		headGizmo.draw(shader, 0);

		shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	}
}

void Scene::Update(float deltaTime) {
	activeCamera->Update(deltaTime);

	if (!gameManager.isGameMode) return;

	gameTime += deltaTime;

	lightingSystem.Update(deltaTime);

	playerObj.Update(deltaTime, gameObjects, activeCamera->front, activeCamera->right);
}

void Scene::ProcessMouseMovement(double xpos, double ypos, bool enableRotation) {
	if (!enableRotation) {
		gameManager.lastX = xpos;
		gameManager.lastY = ypos;
		return;
	}

	if (gameManager.firstMouse) {
		gameManager.lastX = xpos;
		gameManager.lastY = ypos;
		gameManager.firstMouse = false;
	}

	float xoffset = (float)xpos - gameManager.lastX;
	float yoffset = gameManager.lastY - (float)ypos; 

	gameManager.lastX = xpos;
	gameManager.lastY = ypos;

	activeCamera->ProcessMouseMovement(xoffset, yoffset);
}

void Scene::handleMovementInput(GLFWwindow* window, float deltaTime) {
	if (!currentController) return;

	if (gameManager.isGameMode) {
		playerObj.UpdateCameraVectors(activeCamera->front, activeCamera->right);
	}

	inputManager.HandleInput(window, *currentController, deltaTime);
}

bool Scene::updateCursorState(GLFWwindow* window) {
	if (gameManager.isGameMode) return true;

	bool rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	if (rightClick) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return true;
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		gameManager.firstMouse = true;
		return false;
	}
}

GameObject Scene::CreateObject(Mesh* mesh, glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float angle, float rotSpeed, glm::vec3 rotAxis) {
	GameObject obj;
	
	return obj;
}