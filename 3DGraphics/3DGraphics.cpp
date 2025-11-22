#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "GeometryGenerator.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

glm::vec3 lightPos(1.2f, 2.0f, 2.0f);

Camera camera(glm::vec3(1.0f, 0.0f, 0.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

float lastx = SCR_WIDTH / 2.0f;
float lasty = SCR_HEIGHT / 2.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3DGraphics", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	glEnable(GL_DEPTH_TEST);

	Shader myShader("shader.vert", "shader.frag");

	Mesh* cubeMesh = GeometryGenerator::CreateCube();
	Mesh* pyramidMesh = GeometryGenerator::CreatePyramid();

	std::vector<GameObject> gameObjects;

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
    wall.rotationSpeed = 0.0f;
	wall.mesh = cubeMesh;
	gameObjects.push_back(wall);

    GameObject fan;
    fan.position = glm::vec3(2.0f, 0.0f, 0.0f);
    fan.scale = glm::vec3(3.0f, 0.2f, 0.2f); // Длинная палка
    fan.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f); // Крутим вокруг Z (как пропеллер)
    fan.angle = 0.0f;
    fan.rotationSpeed = 200.0f; // <--- КРУТИТСЯ БЫСТРО (градусов в сек)
    fan.mesh = cubeMesh;
    gameObjects.push_back(fan);

	GameObject pyramid;
	pyramid.position = glm::vec3(-2.0f, -1.0f, 0.0f);
	pyramid.scale = glm::vec3(1.0f);
	pyramid.color = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid.rotationAxis = glm::vec3(0.5f, 1.0f, 0.0f);
	pyramid.angle = 0.0f;
	pyramid.rotationSpeed = 0.0f;
	pyramid.mesh = pyramidMesh;
	gameObjects.push_back(pyramid);
    

    while (!glfwWindowShouldClose(window))
    {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		if (SCR_HEIGHT == 0)
            SCR_HEIGHT = 1;
		float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
        
        myShader.use();

		myShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		myShader.setVec3("lightPos", lightPos);
		myShader.setVec3("viewPos", camera.Position());

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		
        myShader.setMat4("projection", projection);
        myShader.setMat4("view", view);
        
        for (const auto& obj : gameObjects) {
            obj.draw(myShader, (float)glfwGetTime());
		}

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	delete cubeMesh;
	delete pyramidMesh;    

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastx = xpos;
        lasty = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; 

	lastx = xpos;
	lasty = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}