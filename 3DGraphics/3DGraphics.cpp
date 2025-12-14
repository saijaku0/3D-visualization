#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h" 
#include "EditorManager.h"

Scene* scene = nullptr;
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Graphics", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    EditorManager editor;
    editor.Init(window);
    scene = new Scene(SCR_WIDTH, SCR_HEIGHT, window);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        scene->ProcessInput(window, deltaTime);

        scene->Update(deltaTime);

        scene->BindFramebuffer();
        glViewport(0, 0, (int)scene->GetWidth(), (int)scene->GetHeight());
        glEnable(GL_DEPTH_TEST);

        if (scene->GetActiveCamera()) {
            scene->GetActiveCamera()->SetAspectRatio((float)SCR_WIDTH, (float)SCR_HEIGHT);
        }

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->Draw(scene->GetWidth(), scene->GetHeight());

        scene->UnbindFramebuffer();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        editor.Draw(scene);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    editor.Shutdown();
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
        scene->ProcessMouseMovement(window, xpos, ypos);
    }
}