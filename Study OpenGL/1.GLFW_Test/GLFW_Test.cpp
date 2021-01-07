
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void processEsc(GLFWwindow *wndw) { // 입력 처리함수
	if (glfwGetKey(wndw, GLFW_KEY_ESCAPE) == GLFW_PRESS) // wndw에서 Esc를 눌렀다면
		glfwSetWindowShouldClose(wndw, true); // 출력종료 명령 내림
}

int main() {
	glfwInit(); // GLFW 초기화
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW의 고유변수(힌트) 초기설정
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); // 출력창 생성
	if (window == NULL) { // 출력창이 잘 만들어졌는지 확인
		cout << "Failed to create Window" << endl;
		glfwTerminate(); // GLFW 강제종료
		return -1;
	}glfwMakeContextCurrent(window); // 지금은 'window'의 내용을 쓸것이라고 알려줌

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // GLAD에 OpenGL 함수포인터 불러오기
		cout << "Failed to start GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600); // 카메라의 시야 범위(직사각형) 
	while (!glfwWindowShouldClose(window)) {  // 출력종료 명령이 들어오기 전까지 반복
		processEsc(window); // Esc 입력체크

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // 창 단색으로 지우기(위에서 색 설정)		

		glfwSwapBuffers(window); // 만들어진 창 이미지 출력
		glfwPollEvents(); // 동작감지
	}

	glfwTerminate(); // GLFW 종료
	return 0;
}