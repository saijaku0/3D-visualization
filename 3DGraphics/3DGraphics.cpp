#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "GeometryGenerator.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

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

	GameObject obj1;
	obj1.position = glm::vec3(-2.0f, 0.0f, 0.0f);
	obj1.rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	obj1.rotationSpeed = 1.0f;
	obj1.scale = 1.0f;
	obj1.mesh = pyramidMesh;
	gameObjects.push_back(obj1);

    GameObject obj2;
    obj2.position = glm::vec3(1.5f, 0.0f, 0.0f);
    obj2.rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
    obj2.rotationSpeed = 0.5f;
    obj2.scale = 0.5f;
    obj2.mesh = pyramidMesh;
    gameObjects.push_back(obj2);

    GameObject obj3;
    obj3.position = glm::vec3(-1.0f, 0.0f, 0.0f);
    obj3.rotationAxis = glm::vec3(1.0f, 1.0f, 0.0f);
    obj3.rotationSpeed = 1.5f;
    obj3.scale = 0.7f;
    obj3.mesh = cubeMesh;
    gameObjects.push_back(obj3);
    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		if (SCR_HEIGHT == 0)
            SCR_HEIGHT = 1;
		float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;
        
        myShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));
		
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
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}