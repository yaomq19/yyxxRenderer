#pragma once
#ifndef RENDERER_H
#define RENDERER_H
//��׼��
#include<vector>
//��������
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//�Զ����
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
