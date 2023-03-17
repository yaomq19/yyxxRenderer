#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#define MY_DEPTH_TEST
#define MY_STENCIL_TEST
//#define MY_BLENDER
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
    /*stbi_set_flip_vertically_on_load(1);
    Renderer r;
    r.init();
    Shader ourShader("3.3.vs", "3.3.fs");
    Model ourModel("resources/objects/window/window.obj");
    Model ourModel2("resources/objects/window/window_noblend.obj");
    r.models.push_back({ ourModel2 ,ourShader });
    r.models.push_back({ ourModel ,ourShader });
    
    
    r.render();
    
    r.destroy();*/
}
void test03()
{
    Renderer r;
    r.init();
    
    Shader skyboxShader("skybox.vs", "skybox.fs");
    
    r.createSkyBox("resources/textures/skybox", skyboxShader);
    
    Shader ourShader("3.3.vert", "3.3.frag");
    Model ourModel("resources/objects/nanosuit/nanosuit.obj");
    r.models.push_back({ ourModel ,ourShader });
    r.render();
    r.destroy();
    
}
void test04()
{
    glm::vec3 result1 = glm::vec3(0.0, 0.0, 0.0);

    glm::vec3 result2;

    glm::vec4 FragColor1 = glm::vec4(result1, 1.0);
    glm::vec4 FragColor2 = glm::vec4(result2, 1.0);
    glm::vec4 FragColor = FragColor1 + FragColor2;
}
int main()
{
    test03();
    return 0;
}

