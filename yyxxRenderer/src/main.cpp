#include<Renderer.h>

int main()
{
	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
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

	//����shader
	Shader shader1 = r.createShader("1.vs","1.fs");
	//����VBO��EBO��VAO��VAP
	VBO vbo = r.createVBO(vertices, sizeof(vertices));
	EBO ebo = r.createEBO(indices,sizeof(indices));
	std::vector<VertexAttribPointer>vaps;
	vaps.push_back(VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	VAO vao=r.createVAO(vbo,ebo,vaps);
	DrawInstruction di("glDrawElements", "GL_TRIANGLES", 0, 6);
	//��һ��VAO��һ��Shader��һ��DI���һ��RU������r�Ĺ���Χ
	r.createRenderUnit(vao, shader1, di);
	
	//�����ȾRenderer�е�ÿ��RU
	r.render();

	r.destroy();
	return 0;
}