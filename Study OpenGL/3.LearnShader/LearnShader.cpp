
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

float vertices[] = { 
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // xyz rgb (Attrib 2종류)
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};

const char* VertexShaderSource = // 정점쉐이더 = 정점&초기입력담당
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // VAO 0번포인터에서 주는 데이터 받기 
"layout (location = 1) in vec3 aColor;\n" // VAO 1번포인터에서 주는 데이터 받기
"uniform float xoffset;\n"
"out vec3 vertexColor;\n" // 이걸 FragmShader로 내보낼것임
"void main(){\n"
"	vertexColor = aColor;\n"
"	gl_Position = vec4(aPos.x+xoffset, aPos.yz, 1.0);\n"
"}\n\0";

const char* FragmShaderSource = // 픽셀쉐이더 = 색칠담당
"#version 330 core\n"
"in vec3 vertexColor;\n" // VertexShader에서 내려받음
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(vertexColor, 1.0);\n" 
"}\n\0";

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

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL); 
	glCompileShader(vertexShader); 
	int good; char Log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &good);
	if (!good) {
		glGetShaderInfoLog(vertexShader, 512, NULL, Log);
		cout << "VERTEX SHADER FAILED!\n" << Log << endl;
	}

	unsigned int fragmShader;
	fragmShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmShader, 1, &FragmShaderSource, NULL); 
	glCompileShader(fragmShader); 
	glGetShaderiv(fragmShader, GL_COMPILE_STATUS, &good); 
	if (!good) {
		glGetShaderInfoLog(vertexShader, 512, NULL, Log);
		cout << "FRAGMENT SHADER FAILED!\n" << Log << endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); 
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &good); 
	if (!good) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, Log);
		cout << "SHADER LINKING FAILED!\n" << Log << endl;  
	}
	glDeleteShader(vertexShader); 
	glDeleteShader(fragmShader);

	unsigned int VBO, VAO; 
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // ㄴ 0번 포인터 VBO에서 정보(좌표) 긁기 ( Float 6개씩에서 0번째부터 3개를 내보냄 )
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1); // ㄴ 1번 포인터 VBO에서 정보(컬러) 긁기 ( Float 6개씩에서 3번째부터 3개를 내보냄 )

	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window)) {
		processEsc(window);
		processFillorNot(window);
		//--------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//--------
		glUseProgram(shaderProgram); // 쉐이더 프로그램 ON
		glBindVertexArray(VAO);
		float time = glfwGetTime();
		int uLocation = glGetUniformLocation(shaderProgram, "xoffset"); // 셰이더에서 xoffset 위치 알아내기
		glUniform1f(uLocation, sin(time)/2.0); // xoffset 위치에 특정값 넘겨줌 (셰이더 내부에선 상수취급됨)
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		//--------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}