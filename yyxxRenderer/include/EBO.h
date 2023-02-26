#pragma once
#ifndef EBO_H
#define EBO_H
#include<glad/glad.h>
class EBO
{
public:
	unsigned int ID;
	EBO()
	{
		glGenBuffers(1, &ID);
	}
	EBO(unsigned int indices[], int size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
	void trasmitData(unsigned int indices[], int size)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
};
#endif // !EBO
