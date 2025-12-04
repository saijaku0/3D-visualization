#include "Scene.h"

Scene::Scene(int width, int height) :
    gameManager(width, height),
    lightingSystem(glm::vec3(0.0f, 1.0f, 0.0f)),
    renderer(),
    gameTime(0.0f),
    pointLightPos(0.0f, 1.0f, 0.0f),
    activeCamera(nullptr),
    skybox(nullptr)
{
    Init();
}

Scene::~Scene() {
    delete skybox;
}

void Scene::Init() {
    SceneFactory::CreateResources(cubeMesh, pyramidMesh);
    SceneFactory::LoadDefaultScene(gameObjects, cubeMesh, pyramidMesh);

    playerObj.transform.Position = glm::vec3(0.0f, 0.0f, 5.0f);
    playerObj.transform.Scale = glm::vec3(0.5f);
    playerObj.color = glm::vec3(1.0f, 0.0f, 0.0f);
    playerObj.mesh = cubeMesh; 
    playerObj.isStatic = false;

    myBall.mesh = cubeMesh;
    myBall.transform.Position = glm::vec3(0.0f, 5.0f, 0.0f); 
    myBall.transform.Scale = glm::vec3(0.5f);
    myBall.color = glm::vec3(0.0f, 1.0f, 1.0f); 
    myBall.elasticity = 0.3f; 

    devCamera = std::make_unique<FreeCamera>(glm::vec3(0.0f, 5.0f, 10.0f));

    playerCamera = std::make_unique<AttachedCamera>(&playerObj, glm::vec3(0.0f, 0.6f, 0.0f));

    activeCamera = devCamera.get();

    skybox = new Skybox();
    std::vector<std::string> faces = {
        "assets/sky_right.png", "assets/sky_left.png",
        "assets/sky_top.png",   "assets/sky_bottom.png",
        "assets/sky_front.png", "assets/sky_back.png"
    };
    skybox->LoadCubemap(faces);
}

void Scene::ProcessInput(GLFWwindow* window, float deltaTime) {
    gameManager.ProcessModeSwitch(
        window,
        devCamera.get(),
        playerCamera.get(),
        &playerObj,
        activeCamera
    );

    if (gameManager.IsGameMode()) {
        playerObj.ProcessInput(
            window,
            activeCamera->GetFront(),
            activeCamera->GetRight()
        );
    }
    else {
        handleMovementInput(window, deltaTime);
    }

    bool cursorEnabled = gameManager.IsMouseRotationActive(window);
    if (cursorEnabled)
        handleMovementInput(window, deltaTime);
}

void Scene::handleMovementInput(GLFWwindow* window, float deltaTime) {
    if (!activeCamera) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Right, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Up, deltaTime); 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        activeCamera->ProcessKeyboard(CameraMovement::Down, deltaTime);

    if (activeCamera == playerCamera.get()) {
        playerObj.ProcessInput(
            window,
            activeCamera->GetFront(),
            activeCamera->GetRight()
        );
    }
}

void Scene::Update(float deltaTime) {
    activeCamera->Update(deltaTime);

    if (gameManager.IsGameMode()) {
        playerObj.Update(deltaTime, gameObjects);

        //std::vector<GameObject> ballObstacles = gameObjects;
        //ballObstacles.push_back(playerObj);
        myBall.Update(deltaTime, gameObjects);

        if (Physics::checkCollisionAABB(myBall, playerObj)) {

            myBall.velocity = -myBall.velocity * myBall.elasticity;

            glm::vec3 separationVector = myBall.transform.Position - playerObj.transform.Position;
            myBall.transform.Position += glm::normalize(separationVector) * 1.0f; 
        }
    }

    if (activeCamera)
        activeCamera->Update(deltaTime);

    gameTime += deltaTime;
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

    myBall.Draw(shader);

    if (!gameManager.IsGameMode()) {
        shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);
        playerObj.Draw(shader);

        GameObject headGizmo;
        headGizmo.transform.Position = playerCamera->GetPosition(); 
        headGizmo.transform.Scale = glm::vec3(0.2f);
        headGizmo.color = glm::vec3(0.0f, 0.0f, 1.0f);
        headGizmo.mesh = cubeMesh;
        headGizmo.Draw(shader);

        shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    }

    if (activeCamera && skybox) {
        glm::mat4 view = glm::mat4(glm::mat3(activeCamera->GetViewMatrix())); 
        float aspectRatio = (float)scrWidth / (float)scrHeight;
        glm::mat4 projection = activeCamera->GetProjectionMatrix(aspectRatio);
        skybox->Draw(view, projection);
    }
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

    if (activeCamera)
	    activeCamera->ProcessMouseMovement(xoffset, yoffset);
}

bool Scene::updateCursorState(GLFWwindow* window) {
	if (gameManager.IsGameMode()) return true;

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
