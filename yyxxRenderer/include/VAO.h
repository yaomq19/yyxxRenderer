#pragma once
#ifndef VAO_H
#define VAO_H
#include<glad/glad.h>
#include<VBO.h>
#include<EBO.h>
struct VertexAttribPointer
{
	GLuint layout;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;
	VertexAttribPointer(GLuint layoutt,
		GLint sizee, 
		GLenum typee, 
		GLboolean normalizedd,
		GLsizei stridee,
		const void* pointerr)
	{
		layout = layoutt;
		size = sizee;
		type = typee;
		normalized = normalizedd;
		stride = stridee;
		pointer = pointerr;
	}
};
class VAO
{
public:
	unsigned int ID;
	VAO()
	{
		glGenVertexArrays(1, &ID);
	}
	VAO(VBO vbo, EBO ebo,std::vector<VertexAttribPointer> vaps)
	{
		glGenVertexArrays(1, &ID);
		glBindVertexArray(ID);

		glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		for(auto &it:vaps)
		{
			glVertexAttribPointer(it.layout, it.size, it.type, it.normalized, it.stride, it.pointer);
			glEnableVertexAttribArray(it.layout);
		}
		glBindVertexArray(0);
	}
	void set(VBO vbo, EBO ebo,VertexAttribPointer vap)
	{
		glBindVertexArray(ID);

		glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(vap.layout, vap.size, vap.type, vap.normalized, vap.stride, vap.pointer);
		glEnableVertexAttribArray(vap.layout);
		glBindVertexArray(0);
	}
};
#endif // !VAO
