#include <stdio.h>
#include "util/types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders.h"

#define GLV_MAJOR 4
#define GLV_MINOR 6

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

// Handles the window resize event
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argv, char **argc)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLV_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLV_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); Fuck MacOS

    // Create window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OGLShit", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Setup general OpenGL settings
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    printf("Hello World!\n");

    printf("%s\n", fragment_shader);
    printf("%s\n", vertex_shader);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Poll and handle events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}