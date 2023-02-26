#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<glad/glad.h>
#include<iostream>
class Texture2D
{
public:
	unsigned int ID;
	/*Texture2D()
	{
		glGenTextures(1, &ID);
	}*/
	Texture2D(const char* path);
	void set()
	{

	}
};
#endif // !TEXTURE_H
