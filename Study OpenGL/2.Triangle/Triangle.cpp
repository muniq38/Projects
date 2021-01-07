
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

float vertices[] = { // 정점데이터 (좌표 -1~1)
	0.5f, 0.5f, 0.0f, // 0번정점 
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f // 5번정점
};

unsigned int indices[] = { // 도형데이터 (정점 번호들로 구성)
	0, 1, 2, // 0번도형
	1, 4, 2  // 1번도형
};

const char* VertexShaderSource = // 정점쉐이더 코드 (GLSL) .vs
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char* FragmShaderSource = // 픽셀쉐이더 코드 (GLSL) .fs
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "TRIANGLE + TRIANGLE = RECTANGLE", NULL, NULL);
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
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // 쉐이더 유형 설정(정점쉐이더)
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL); // 정점쉐이더 소스 가져오기
	glCompileShader(vertexShader); // 소스 자체 컴파일
	int good; char Log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &good); // 컴파일 잘됐는지 확인
	if (!good) {
		glGetShaderInfoLog(vertexShader, 512, NULL, Log);
		cout << "VERTEX SHADER FAILED!\n" << Log << endl;  // 에러메시지 출력
	}

	unsigned int fragmShader;
	fragmShader = glCreateShader(GL_FRAGMENT_SHADER); // 쉐이더 유형 설정(픽셀쉐이더)
	glShaderSource(fragmShader, 1, &FragmShaderSource, NULL); // 픽셀쉐이더 소스 가져오기
	glCompileShader(fragmShader); // 소스 자체 컴파일
	glGetShaderiv(fragmShader, GL_COMPILE_STATUS, &good); // 컴파일 잘됐는지 확인
	if (!good) {
		glGetShaderInfoLog(vertexShader, 512, NULL, Log);
		cout << "FRAGMENT SHADER FAILED!\n" << Log << endl;  // 에러메시지 출력
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); // 쉐이더들을 합쳐서 프로그램 형태로 완성할거임
	glAttachShader(shaderProgram, vertexShader); // 쉐이더를 프로그램에 하나씩 붙이기
	glAttachShader(shaderProgram, fragmShader);
	glLinkProgram(shaderProgram); // 붙인 쉐이더들 연결하기(용접?)
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &good); // 용접 잘됐는지 확인 
	if (!good) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, Log);
		cout << "SHADER LINKING FAILED!\n" << Log << endl;  // 에러메시지 출력
	}
	glDeleteShader(vertexShader); // 프로그램 만들고 남은 쉐이더들은 폐기
	glDeleteShader(fragmShader);

	unsigned int VBO, VAO, EBO; // VBO는 정점저장버퍼, VAO는 정점저장배열, EBO는 도형저장버퍼
	glGenVertexArrays(1, &VAO); // 역할설정
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO); // VAO 바인딩(함수와 연결)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO 버퍼(GAB)와 연동
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // EBO 버퍼(GEAB)와 연동
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// VAO의 0번 포인터가 VBO에서 정보 읽어들임 ( Float 3개씩 묶어서 0번째부터 3개를 내보냄 )
	glEnableVertexAttribArray(0); // 0번 포인터 활성화 (쉐이더에서 읽음)

	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window)) {
		processEsc(window);
		processFillorNot(window);
		//--------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//--------
		glUseProgram(shaderProgram); // 쉐이더 프로그램 사용 (첫줄)
		glBindVertexArray(VAO); // VAO 바인딩
		//glDrawArrays(GL_TRIANGLES, 0, 6); // VBO의 0번째부터 6개의 정점을 꺼내 삼각형 그리기 or
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // EBO의 ,, 인덱스를 꺼내 삼각형 그리기
		//--------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
