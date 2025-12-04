#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"

glm::vec3 lightPos(1.2f, 2.0f, 2.0f);

Scene* scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

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
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	glEnable(GL_DEPTH_TEST);

	Shader myShader("shader.vert", "shader.frag");

    scene = new Scene(SCR_WIDTH, SCR_HEIGHT);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        scene->ProcessInput(window, deltaTime);

        scene->Update(deltaTime);

        //glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
        scene->Draw(myShader, SCR_WIDTH, SCR_HEIGHT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	delete scene;
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (scene) {
        GameManager& gm = scene->GetGameManager();

		bool isRightDown = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
		bool shouldRotation = gm.IsGameMode() || isRightDown;
        scene->ProcessMouseMovement(xpos, ypos, shouldRotation);
    }
}