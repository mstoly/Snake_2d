#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "Model.h"
#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    auto *renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
    if (renderer)
    {
        renderer->OnResize(width, height);
    }
}

int main(void)
{
    const double tickRate = 2.0;
    const double tickTime = 1.0 / tickRate;

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Snake", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
        glfwTerminate();
        return -1;
    }

    auto pModel = std::make_unique<Model>();
    auto pRenderer = std::make_unique<Renderer>();

    glfwSetWindowUserPointer(window, pRenderer.get());
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.1, 0.3, 0, 1);

    double previousTime = glfwGetTime();
    double lag = 0.0;
    double currentTime{};
    double elapsed{};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        elapsed = currentTime - previousTime;

        previousTime = currentTime;
        lag += elapsed;

        /* Poll for and process events */
        glfwPollEvents();

        while (lag >= tickTime)
        {
            pModel->Update();
            lag -= tickTime;
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        pRenderer->Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
