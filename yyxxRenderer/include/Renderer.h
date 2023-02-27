#pragma once
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
#ifndef RENDERER_H
#define RENDERER_H
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
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
class Renderer
{
public:
	bool init(unsigned int major_version, unsigned int minor_version);
	bool render();//¥∞ø⁄ µ ±‰÷»æ
	bool destroy();
	
	Shader createShader(const char* vertexPath, const char* fragmentPath)
	{
		Shader shader(vertexPath, fragmentPath);
		shaders.push_back(shader);
		return shader;
	}
	VBO createVBO(float vertices[], int size)
	{
		VBO vbo(vertices, size);
		VBOs.push_back(vbo);
		return vbo;
	}
	EBO createEBO(unsigned int indices[],int size)
	{
		EBO ebo(indices, size);
		EBOs.push_back(ebo);
		return ebo;
	}
	VAO createVAO(VBO vbo, EBO ebo, std::vector<VertexAttribPointer> vaps)
	{
		VAO vao(vbo, ebo, vaps);
		VAOs.push_back(vao);
		return vao;
	}
	int createTexture2D(const char* path)
	{
		if (numOfTextures >= 16) {
			std::cout << "Failed to create texture: too many textures over 16" << std::endl;
			return -1;
		}
		glActiveTexture(GL_TEXTURE0 + numOfTextures);
		
		Texture2D t2d(path);

		int res = numOfTextures;
		numOfTextures++;
		return res;
	}
	void createRenderUnit(VAO vao, Shader shader,DrawInstruction di,std::vector<glm::mat4> models)
	{
		renderUnits.push_back(RenderUnit(vao.ID,shader.ID,di, models));
	}
	
	void setView(glm::vec3 trans) {
		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		view = glm::translate(view, trans);
		this->view = view;
	}
	void setProjection(float angle, float near, float far) {
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(angle), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
		this->projection = projection;
	}

private:
	const int SCR_WIDTH = 800;
	const int SCR_HEIGHT = 600;
	GLFWwindow* window;
	Camera camera;
	std::vector<Light> lights;
	std::vector<Item> items;
	std::vector<Shader> shaders;
public:
	std::vector<VAO> VAOs;
	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
	//std::vector<Texture2D> texture2Ds;
	unsigned int textures[16];
	int numOfTextures = 0;

	glm::mat4 view = glm::mat4(1.0f);;
	glm::mat4 projection = glm::mat4(1.0f);;

	std::vector<RenderUnit> renderUnits;
	//settings

private:
	/* init */
	void glfwinit(unsigned int major_version, unsigned int minor_version);
	bool createWindow();
	void setCallBackForWindow();
	bool gladLoad();
	/* render */
	void processInput(GLFWwindow* window);
};
#endif // !RENDERER_H
