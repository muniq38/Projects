
//#ifndef SHADER_H // ¸¸¾à Shader Class¸¦ Çì´õ·Î ¸¸µé°í ½ÍÀ» ¶§ »ç¿ë
//#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/Shader.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

float vertices[] = {
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // xyz rgb (Attrib 2Á¾·ù)
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};

void processEsc(GLFWwindow *wndw) {
	if (glfwGetKey(wndw, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(wndw, true);
}

void processFillorNot(GLFWwindow *wndw) {
	if (glfwGetKey(wndw, GLFW_KEY_ENTER) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Glowing Something", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create Window" << endl;
		glfwTerminate();
		return -1;
	}glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to start GLAD" << endl;
		return -1;
	}

	Shader ourShader("vertexShader.vs", "fragmShader.fs"); // Á¤Á¡½¦ÀÌ´õ¿Í ÇÈ¼¿½¦ÀÌ´õ ÁÂÇ¥ Âï¾îÁØ °´Ã¼ »ý¼º

	//Data Part
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window)) {
		processEsc(window);
		processFillorNot(window);
		//--------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//--------
		ourShader.use();
		glBindVertexArray(VAO);
		float time = glfwGetTime();
		ourShader.setFloat("xoffset", sin(time) / 2.0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//--------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

// #endif