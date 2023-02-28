#pragma once
#ifndef RENDERER_H
#define RENDERER_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<Camera.h>
#include<Light.h>
#include<Item.h>
#include<Shader.h>
#include<VAO.h>
#include<Texture.h>
//#include<stb_image.h>

#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include <sstream>

struct DrawInstruction
{
	std::string cmd;
	std::string primitive;
	int start;
	int count;
	DrawInstruction(std::string a, std::string b,int c,int d)
	{
		cmd = a;
		primitive = b;
		start = c;
		count = d;
	}
};
struct RenderUnit
{
	unsigned int VAOId;
	unsigned int ShaderId;
	DrawInstruction di;
	std::vector<glm::mat4>models;
	RenderUnit(unsigned int a, unsigned int b, DrawInstruction c,
		std::vector<glm::mat4> d) :VAOId(a), ShaderId(b), di(c),models(d){}
};
class Renderer
{
public:
	bool init(unsigned int major_version, unsigned int minor_version);
	bool render();//¥∞ø⁄ µ ±‰÷»æ
	bool destroy();
	
	Shader createShader(const char* vertexPath, const char* fragmentPath);
	VBO createVBO(float vertices[], int size);
	EBO createEBO(unsigned int indices[], int size);
	VAO createVAO(VBO vbo, EBO ebo, std::vector<VertexAttribPointer> vaps);
	int createTexture2D(const char* path);
	void createRenderUnit(VAO vao, Shader shader, DrawInstruction di, std::vector<glm::mat4> models);
	void setView(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void setProjection(float angle, float near, float far);

private:
	const int SCR_WIDTH = 800;
	const int SCR_HEIGHT = 600;
	float lastX , lastY ;
	float xpos, ypos;
	GLFWwindow* window;

	Camera camera;
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	std::vector<VAO> VAOs;
	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
	int numOfTextures = 0;
	unsigned int textures[16];
	std::vector<Light> lights;
	std::vector<Item> items;
	std::vector<Shader> shaders;
	std::vector<RenderUnit> renderUnits;
private:
	/* init */
	void glfwinit(unsigned int major_version, unsigned int minor_version);
	bool createWindow();
	bool gladLoad();
	/* render */
	void processInput(GLFWwindow* window);
};
#endif // !RENDE
