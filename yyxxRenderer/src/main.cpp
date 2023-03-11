#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/Renderer.h>

#include <iostream>


void test01()
{
    Renderer r;
    r.init();
    Shader ourShader("3.3.vs", "3.3.fs");
    Model ourModel("resources/objects/nanosuit/nanosuit.obj");
    r.models.push_back({ ourModel ,ourShader });
    r.render();
    r.destroy();
}
void test02()
{
    float points[] = {
    -0.5f,  0.5f, // 左上
     0.5f,  0.5f, // 右上
     0.5f, -0.5f, // 右下
    -0.5f, -0.5f  // 左下
    };
    Renderer r;
    r.init();
    Shader shader("9.3.vs", "9.3.fs", "9.3.gs");
    while (!glfwWindowShouldClose(r.window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(r.window);

        // render
        // ------
        glClearColor(0.2f, 0.6f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glfwSwapBuffers(r.window);
        glfwPollEvents();
    }
    r.destroy();
}
int main()
{
    test01();
    return 0;
}

