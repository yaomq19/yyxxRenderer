#pragma once
#ifndef RENDERER_H
#define RENDERER_H
//标准库
#include<vector>
//第三方库
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//自定义库
#include<Model.h>
using namespace std;

class Renderer
{
public:
	bool init(unsigned int major_version=3, 
		unsigned int minor_version=3,
		unsigned int sw = 800,
		unsigned int sh = 600);
	bool destroy();
	void render();
	void loadModel(const char* path, const Shader& shader);
private:
	int SCR_WIDTH;
	int SCR_HEIGHT;
	GLFWwindow* window;
public:
	std::vector<pair<Model, Shader>> models;
private:
};
#endif // !RENDE
