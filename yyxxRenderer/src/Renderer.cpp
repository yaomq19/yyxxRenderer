#include<Renderer.h>
float globalX, globalY;
bool firstMouse = true;
/* global function start */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	globalX = xpos;
	globalY = ypos;
}
float globalScroll = 0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	globalScroll = yoffset;
}
/* global function end */
/* class Renderer start */
/* public */
bool Renderer::init(unsigned int major_version, unsigned int minor_version)
{
	glfwinit(major_version, minor_version);
	if (!createWindow())return false;
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoad())return false;
	glEnable(GL_DEPTH_TEST);
	return true;
}
bool Renderer::render()
{
	while (!glfwWindowShouldClose(window))
	{
		for (auto& it : modelsWithShaders)
		{
			it.first.Draw(*(it.second));
		}
		//what input would use
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrameTime;
		lastFrameTime = currentFrame;
		float trueSpeed = camera.Speed * deltaTime;
		// input
		// -----
		processInput(window);
		float xoffset = 0;
		float yoffset = 0;
		if (lastX != globalX || lastY != globalY)
		{
			if (firstMouse) {
				lastX = globalX;
				lastY = globalY;
				firstMouse = false;
			}
			xoffset = globalX - lastX;
			yoffset = lastY - globalY;
			lastX = globalX;
			lastY = globalY;
		}
		camera.ProcessMouseMovement(xoffset, yoffset);
		setView(camera.Pos, camera.Pos + camera.Front, camera.Up);

		if (globalScroll != 0) {
			camera.ProcessMouseScroll(static_cast<float>(globalScroll));
			globalScroll = 0;
		}
		setProjection(camera.Zoom, 0.1f, 100.0f);
		//std::cout << camera.Zoom << std::endl;
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//渲染渲染器内部加载的模型
		// 渲染main函数中自定义模型
		for (auto& it : renderUnits)
		{
			glUniformMatrix4fv(glGetUniformLocation(it.ShaderId, "view"), 1, GL_FALSE, &(view[0][0]));
			glUniformMatrix4fv(glGetUniformLocation(it.ShaderId, "projection"), 1, GL_FALSE, &(projection[0][0]));
			for (auto& model : it.models) {
				glUseProgram(it.ShaderId);
				glUniformMatrix4fv(glGetUniformLocation(it.ShaderId, "model"), 1, GL_FALSE, &(model[0][0]));
				
				glBindVertexArray(it.VAOId);
				if (it.di.cmd == "glDrawArrays") {
					if (it.di.primitive == "GL_TRIANGLES") {
						glDrawArrays(GL_TRIANGLES, it.di.start, it.di.count);
					}
				}
				else if (it.di.cmd == "glDrawElements") {
					if (it.di.primitive == "GL_TRIANGLES") {
						glDrawElements(GL_TRIANGLES, it.di.count, GL_UNSIGNED_INT, (void*)it.di.start);
					}
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

Shader Renderer::createShader(const char* vertexPath, const char* fragmentPath)
{
	Shader shader(vertexPath, fragmentPath);
	shaders.push_back(shader);
	return shader;
}
VBO Renderer::createVBO(float vertices[], int size)
{
	VBO vbo(vertices, size);
	VBOs.push_back(vbo);
	return vbo;
}
EBO Renderer::createEBO(unsigned int indices[], int size)
{
	EBO ebo(indices, size);
	EBOs.push_back(ebo);
	return ebo;
}
VAO Renderer::createVAO(VBO vbo, EBO ebo, std::vector<VertexAttribPointer> vaps)
{
	VAO vao(vbo, ebo, vaps);
	VAOs.push_back(vao);
	return vao;
}
int Renderer::createTexture2D(const char* path)
{
	if (numOfTextures >= 16) {
		std::cout << "Failed to create texture: too many textures over 16" << std::endl;
		return -1;
	}
	glActiveTexture(GL_TEXTURE0 + numOfTextures);

	Texture2D t2d(path);

	int res = numOfTextures;
	numOfTextures++;
	return res;
}
void Renderer::createRenderUnit(VAO vao, Shader shader, DrawInstruction di, std::vector<glm::mat4> models)
{
	renderUnits.push_back(RenderUnit(vao.ID, shader.ID, di, models));
}
void Renderer::setView(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	this->view = glm::lookAt(pos, target, up);
}
void Renderer::setProjection(float angle, float near, float far) {
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(angle), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
	this->projection = projection;
}
/* private */
//init
void Renderer::glfwinit(unsigned int major_version, unsigned int minor_version)
{
	glfwInit();
	//设置glfw的主版本号为3，次版本号也为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
	//使用glfw的核心模式
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
	//将窗口window的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.goAhead();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.goBack();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.goLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.goRight();
}
/* class Renderer end */

