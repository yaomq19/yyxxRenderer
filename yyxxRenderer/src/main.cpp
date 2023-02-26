#include<Renderer.h>

int main()
{
	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
	};
	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	Renderer r;
	r.init(3, 3);

	//生成shader
	Shader shader1 = r.createShader("1.vs","1.fs");
	//生成VBO，EBO，VAO，VAP
	VBO vbo = r.createVBO(vertices, sizeof(vertices));
	EBO ebo = r.createEBO(indices,sizeof(indices));
	std::vector<VertexAttribPointer>vaps;
	vaps.push_back(VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	VAO vao=r.createVAO(vbo,ebo,vaps);
	DrawInstruction di("glDrawElements", "GL_TRIANGLES", 0, 6);
	//由一个VAO，一个Shader和一个DI组成一个RU，加入r的管理范围
	r.createRenderUnit(vao, shader1, di);
	
	//逐个渲染Renderer中的每个RU
	r.render();

	r.destroy();
	return 0;
}