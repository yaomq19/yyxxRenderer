#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/Renderer.h>

#include <iostream>



int main()
{
    Renderer r;
    r.init();
    Shader ourShader("3.3.vs", "3.3.fs");
    Model ourModel("resources/objects/091_Aya/091_Aya.obj");
    Model ourModel2("resources/objects/nanosuit/nanosuit.obj");
    r.models.push_back({ ourModel ,ourShader });
    r.models.push_back({ ourModel2 ,ourShader });
    r.render();
    r.destroy();
    return 0;
}

