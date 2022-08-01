#include <stdio.h>
#include "util/types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders.h"

#define GLV_MAJOR 3
#define GLV_MINOR 3

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

    float vertices[] = {
        0.5f,  0.5f,  0.0f,    // top right
        0.5f,  -0.5f, 0.0f,    // bottom right
        -0.5f, -0.5f, 0.0f,    // bottom left
        -0.5f, 0.5f,  0.0f     // top left
    };
    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3     // second triangle
    };

    u32 vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Use shader
    u32 program;
    program = compile_program(vertex_shader_source, fragment_shader_source);
    if (program == -1)
    {
        printf("Failed to compile program\n");
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        // Poll and handle events
        glfwPollEvents();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}