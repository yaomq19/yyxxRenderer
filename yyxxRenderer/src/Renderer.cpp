#include<Renderer.h>
/* class Renderer start */
/* public */
bool Renderer::init(unsigned int major_version, unsigned int minor_version)
{
	glfwinit(major_version, minor_version);
	if (!createWindow())return false;
	setCallBackForWindow();
	if (!gladLoad())return false;

	return true;
}
bool Renderer::render()
{
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//��Ⱦ��Ⱦ���ڲ����ص�ģ��
		// ��Ⱦmain�������Զ���ģ��
		for (auto& it : renderUnits)
		{
			glUseProgram(it.ShaderId);
			glBindVertexArray(it.VAOId);
			if (it.di.cmd == "glDrawArrays"){
				if (it.di.primitive == "GL_TRIANGLES") {
					glDrawArrays(GL_TRIANGLES, it.di.start, it.di.count);
				}
			}
			else if (it.di.cmd == "glDrawElements"){
				if (it.di.primitive == "GL_TRIANGLES"){
					glDrawElements(GL_TRIANGLES, it.di.count, GL_UNSIGNED_INT, (void*)it.di.start);
				}
			}
		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return true;
}
bool Renderer::destroy()
{
	glfwTerminate();
	return true;
}


/* private */
//init
void Renderer::glfwinit(unsigned int major_version, unsigned int minor_version)
{
	glfwInit();
	//����glfw�����汾��Ϊ3���ΰ汾��ҲΪ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
	//ʹ��glfw�ĺ���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}
bool Renderer::createWindow()
{
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	//������window������������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
}
void Renderer::setCallBackForWindow()
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
bool Renderer::gladLoad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return false;
	}
}
//render
void Renderer::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
/* class Renderer end */

/* global function start */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
/* global function end */