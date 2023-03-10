#define STB_IMAGE_IMPLEMENTATION
#include<Renderer.h>
int main()
{
    float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    Renderer r;
    r.init(3, 3,800,600);
    /*Model model;
    Mesh mesh;

    Vertex v1,v2,v3,v4;
    v1.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    v2.Position = glm::vec3(0.5f, -0.5f, 0.0f);
    v3.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
    v4.Position = glm::vec3(-0.5f, 0.5f, 0.0f);
    mesh.vertices.push_back(v1);
    mesh.vertices.push_back(v2);
    mesh.vertices.push_back(v3);
    mesh.vertices.push_back(v4);

    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(3);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);
    mesh.indices.push_back(3);

    mesh.setupMesh();
    Texture texture;
    texture.id = TextureFromFile("cat.jpeg", "./image");
    texture.type = "texture_diffuse";
    texture.path = "cat.jpeg";
    mesh.texture.push_back(texture);

    model.meshes.push_back(mesh);
    
    Shader shader("./shaderSourceCode/1.vs", "./shaderSourceCode/1.fs");
    r.models.push_back({ model ,shader });
    */
    Shader shader("./shaderSourceCode/1.vs", "./shaderSourceCode/1.fs");
    shader.use();
    r.loadModel("./obj/nanosuit.obj", shader);
    r.render();
    r.destroy();
}
