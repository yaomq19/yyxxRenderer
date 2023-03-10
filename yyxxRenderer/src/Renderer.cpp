#include<Renderer.h>
#include<iostream>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
bool Renderer::init(unsigned int major_version,
	unsigned int minor_version,
	unsigned int sw,
	unsigned int sh)
{
	//窗口大小设置
	SCR_WIDTH = sw;
	SCR_HEIGHT = sh;
	//glfw设置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	//回调函数设置
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glad设置
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}
void Renderer::render()
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
		for (auto& it : models) {
			it.first.Draw(it.second);
		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void Renderer::loadModel(const char* path, const Shader& shader)
{
	Model ourModel(path);
	models.push_back({ ourModel ,shader });
}
bool Renderer::destroy()
{
	glfwTerminate();
	return true;
}


