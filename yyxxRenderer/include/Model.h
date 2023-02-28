#pragma once
#ifndef MODEL_H
#define MODEL_H
#include<glm/glm.hpp>
#include<string>
#include<vector>
#include<Shader.h>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

struct Vertex
{
	glm::vec3 Pos;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
class Texture
{
public:
	unsigned int id;
	std::string type;
	Texture() {}
	Texture(const char* path);
};
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int>indices;
	std::vector<Texture> texture;

	Mesh(std::vector<Vertex> vertices,
		std::vector<unsigned int>indices,
		std::vector<Texture> texture);
	void Draw(Shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
class Model
{
public:
	Model(const char* path);
	Model(std::vector<Mesh> meshes);
	void Draw(Shader shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode* node,const aiScene *scene);
	Mesh processMesh(aiMesh* mesh,const aiScene *scene);
	std::vector<Texture> loadMaterialTextures
	   (aiMaterial *mat,
		aiTextureType type,
		std::string typeName);
};
#endif // !MESH_H
