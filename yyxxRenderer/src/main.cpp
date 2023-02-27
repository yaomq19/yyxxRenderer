#include<Renderer.h>
int main()
{
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���

		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	Renderer r;
	r.init(3, 3);
	//��������
	int ActiveTexture0 = r.createTexture2D("image/cat.jpeg");
	int ActiveTexture1 = r.createTexture2D("image/wall.jpg");
	//����shader
	Shader shader1 = r.createShader("shaderSourceCode/1.vs","shaderSourceCode/1.fs");
	shader1.use();
	shader1.setInt("texture1", ActiveTexture0);
	shader1.setInt("texture2", ActiveTexture1);

	//����VBO��EBO��VAO��VAP
	VBO vbo = r.createVBO(vertices, sizeof(vertices));
	EBO ebo = r.createEBO(indices,sizeof(indices));
	std::vector<VertexAttribPointer>vaps;
	vaps.push_back(VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	vaps.push_back(VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))));
	vaps.push_back(VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
	VAO vao=r.createVAO(vbo,ebo,vaps);
	DrawInstruction di("glDrawElements", "GL_TRIANGLES", 0, 6);
	
	//��һ��VAO��һ��Shader��һ��DI���һ��RU������r�Ĺ���Χ
	r.createRenderUnit(vao, shader1, di);
	
	//�����ȾRenderer�е�ÿ��RU
	r.render();

	r.destroy();
	return 0;
}