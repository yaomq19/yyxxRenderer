#pragma once
#ifndef VBO_H
#define VBO_H
#include<glad/glad.h>

class VBO
{
public:
	unsigned int ID;
	VBO() 
	{
		glGenBuffers(1, &ID);
	}
	VBO(float vertices[],int size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	void trasmitData(float vertices[],int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
};
#endif // !VBO
