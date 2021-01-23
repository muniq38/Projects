
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/Shader.h>
#include <GLFW/stb_image.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
using namespace glm;

float vertices[] = { // 오브젝트(Cube)의 Vertex 정보들
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // Pos(XYZ), Normal(XYZ)
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // 6개의 점이 한 면을 담당

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float texCoords[] = { // 1x1 텍스쳐 이미지에서 얼마나 잘라 사용할 것인지
	0.0, 0.0, // 1번점(S,T)
	1.0, 0.0,
	0.5, 1.0
};

vec3 cubePos[] = { // 오브젝트 여러개를 생성할 위치 - 적용은 Model Matrix에서
	vec3(0.0f,  0.0f,  0.0f),
	vec3(2.0f,  5.0f, -15.0f),
	vec3(-1.5f, -2.2f, -2.5f),
	vec3(-3.8f, -2.0f, -12.3f),
	vec3(2.4f, -0.4f, -3.5f),
	vec3(-1.7f,  3.0f, -7.5f),
	vec3(1.3f, -2.0f, -2.5f),
	vec3(1.5f,  2.0f, -2.5f),
	vec3(1.5f,  0.2f, -1.5f),
	vec3(-1.3f,  1.0f, -1.5f)
};

float Time() { return glfwGetTime(); } 
float Rad(float deg) { return radians(deg); }

// 카메라 관련작업 세가지 processMove, processMouse, processScroll
float DelTime = 0.0, LastFrame = 0.0, CurFrame = 0.0;
vec3 camPos = vec3(-8.0, -2.0, 3.0), camTarg = normalize(vec3(8.9, 2.9, -3.5)), camUp = vec3(0.0, 1.0, 0.0); 
void processMove(GLFWwindow *wndw) {
	float camSpeed = 3 * DelTime; 
	if (glfwGetKey(wndw, GLFW_KEY_W) == GLFW_PRESS) camPos += camSpeed * camTarg; 
	if (glfwGetKey(wndw, GLFW_KEY_A) == GLFW_PRESS) camPos -= camSpeed * normalize(cross(camTarg, camUp)); 
	if (glfwGetKey(wndw, GLFW_KEY_S) == GLFW_PRESS) camPos -= camSpeed * camTarg; 
	if (glfwGetKey(wndw, GLFW_KEY_D) == GLFW_PRESS) camPos += camSpeed * normalize(cross(camTarg, camUp)); 
}

float lastX = 400, lastY = 300, sensitivity = 0.05, Yaw, Pitch, YawRad, PitchRad;
bool firstMouse = true;
void processMouse(GLFWwindow *wndw, double curX, double curY) {
	if (firstMouse) {
		curX = lastX; curY = lastY; 
		firstMouse = false;
	}
	float xoffset = (curX - lastX) * sensitivity; 
	float yoffset = (curY - lastY) * sensitivity;
	lastX = curX; lastY = curY;

	Yaw += xoffset;
	Pitch = min(89.0f, Pitch - yoffset);
	Pitch = max(-89.0f, Pitch - yoffset);
	YawRad = Rad(Yaw); PitchRad = Rad(Pitch); 
	camTarg = normalize(vec3(cos(YawRad)*cos(PitchRad), sin(PitchRad), sin(YawRad)*cos(PitchRad))); 
}

float fov = 45.0f; 
void processScroll(GLFWwindow *wndw, double xoffset, double yoffset) {
	fov = max(min(45.0,fov-yoffset), 1.0); 
}

void processEsc(GLFWwindow *wndw) {
	if (glfwGetKey(wndw, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(wndw, true);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float winWidth = 800, winHeight = 600;
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Kane Sorry", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create Window" << endl;
		glfwTerminate();
		return -1;
	}glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, processMouse); // 마우스 관련 입력(이동+스크롤)을 함수로 송출하도록 설정
	glfwSetScrollCallback(window, processScroll);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to start GLAD" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	Shader lightShader("Shader/vertexShader.vs", "Shader/fragmShader.fs");
	Shader CubeShader("Shader/vertexPhong.vs", "Shader/fragmPhong.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int cubeVAO; // 다른 색을 가지는 오브젝트를 위해 새 VAO를 만듬
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // 0번 포인터에서 폴리곤 좌표 긁고 쉐이더로 전달
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1); // 1번 포인터에서 폴리곤 법선벡터 긁고 쉐이더로 전달

	glViewport(0, 0, 800, 600);
	mat4 modelMat, viewMat, projMat;
	vec3 LightPos = vec3(1.2, 1.0, 2.0), LightColor;
	while (!glfwWindowShouldClose(window)) {
		CurFrame = Time(); // 반복할 때마다 시간 기록, 프레임 측정으로 움직임 결정
		DelTime = CurFrame - LastFrame; LastFrame = CurFrame;
		processEsc(window);
		processMove(window);
		//----------
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//----------
		viewMat = projMat = mat4(1.0); // 카메라와 투영 설정 (코드는 그대로)
		viewMat = lookAt(camPos, camTarg + camPos, camUp);
		projMat = perspective(radians(fov), winWidth / winHeight, 0.1f, 100.0f);

		lightShader.use(); // 1번객체 - 빛
		lightShader.setMat4("viewMat", viewMat);
		lightShader.setMat4("projMat", projMat);
		modelMat = mat4(1.0);
		modelMat = translate(modelMat, LightPos);
		modelMat = scale(modelMat, vec3(0.2));
		lightShader.setMat4("modelMat", modelMat);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		CubeShader.use(); // 2번객체 - 사물
		CubeShader.setVec3("light.pos", LightPos); // 광원 위치
		CubeShader.setVec3("camPos", camPos); // 카메라 위치

		LightColor = vec3(sin(Time()*2.0), sin(Time()*0.7), sin(Time()*1.3));
		CubeShader.setVec3("light.ambCof", vec3(0.1)*LightColor); // 반사 계수들
		CubeShader.setVec3("light.diffCof", vec3(0.5)*LightColor);
		CubeShader.setVec3("light.specCof", vec3(1.0));
		CubeShader.setVec3("material.ambCof", vec3(1.0, 0.5, 0.3));
		CubeShader.setVec3("material.diffCof", vec3(1.0, 0.5, 0.3));
		CubeShader.setVec3("material.specCof", vec3(0.5, 0.5, 0.5));
		CubeShader.setFloat("material.alpha", 32.0);

		CubeShader.setMat4("viewMat", viewMat);
		CubeShader.setMat4("projMat", projMat);
		modelMat = mat4(1.0);
		CubeShader.setMat4("modelMat", modelMat);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//--------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
