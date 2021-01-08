
//#ifndef SHADER_H // 만약 Shader Class를 헤더로 만들고 싶을 때 사용
//#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

float vertices[] = {
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // xyz rgb (Attrib 2종류)
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};

class Shader { // 외부 파일에서 쉐이더 긁고 처리하는 Class 만듬 - 헤더로도 따로 빼낼수 있음, main 단순화
public:
	unsigned int Program;
	Shader(const char* vertexPath, const char* fragmPath) { // 생성자, 만들었던 쉐이더 코드 동봉
		string vertexCode, fragmCode;
		ifstream vShaderFile, fShaderFile;
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			vShaderFile.open(vertexPath); // 열기
			fShaderFile.open(fragmPath);
			stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf(); // 읽기
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close(); // 닫기
			fShaderFile.close();
			vertexCode = vShaderStream.str(); // 문자열로 변환
			fragmCode = fShaderStream.str();
		}
		catch (ifstream::failure e) { cout << "SHADER FILE READING FAILED!" << endl; }
		const char* vShaderCode = vertexCode.c_str(); // 최종 코드
		const char* fShaderCode = fragmCode.c_str();

		int good; char Log[512]; // 여기부터는 main에 썼던거랑 같음
		unsigned int vShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vShaderCode, NULL);
		glCompileShader(vShader);
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &good);
		if (!good) {
			glGetShaderInfoLog(vShader, 512, NULL, Log);
			cout << "VERTEX SHADER FAILED!\n" << Log << endl;
		}

		unsigned int fShader;
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fShaderCode, NULL);
		glCompileShader(fShader);
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &good);
		if (!good) {
			glGetShaderInfoLog(fShader, 512, NULL, Log);
			cout << "FRAGMENT SHADER FAILED!\n" << Log << endl;
		}

		Program = glCreateProgram();
		glAttachShader(Program, vShader);
		glAttachShader(Program, fShader);
		glLinkProgram(Program);
		glGetProgramiv(Program, GL_LINK_STATUS, &good);
		if (!good) {
			glGetProgramInfoLog(Program, 512, NULL, Log);
			cout << "SHADER LINKING FAILED!\n" << Log << endl;
		}
		glDeleteShader(vShader);
		glDeleteShader(fShader);
	}
	void use() { glUseProgram(Program); } // 프로그램 사용, Uniform 상수값 전달 등을 함수로 재정의
	void setBool(const string &name, bool Val) { glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)Val); }
	void setInt(const string &name, int Val) { glUniform1i(glGetUniformLocation(Program, name.c_str()), Val); }
	void setFloat(const string &name, float Val) { glUniform1f(glGetUniformLocation(Program, name.c_str()), Val); }
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

	Shader ourShader("vertexShader.vs", "fragmShader.fs"); // 정점쉐이더와 픽셀쉐이더 좌표 찍어준 객체 생성

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