
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
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, // Pos(XYZ), Normal(XYZ), TexCoord(ST)
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, // 6개의 점이 한 면을 담당

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Shading Texture", NULL, NULL);
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
	Shader CubeShader("Shader/vertexPhongCaster.vs", "Shader/fragmPhongCaster.fs");

	unsigned int texture; // 텍스쳐 불러오기 작업
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 여백을 어떻게 채울 것인지
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 축소할때 NEAREST(픽셀)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 확대할때 LINEAR(보간)
	int width, height, RGB;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("Tex/NEWw.JPG", &width, &height, &RGB, 0); // 파일이미지 data에 저장하기
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // data로부터 끌어오기
		glGenerateMipmap(GL_TEXTURE_2D); // 이미지를 밉맵 형태로 변환하기
	}
	else cout << "Failed to load texture" << endl;
	stbi_image_free(data); // 다 쓴 data 폐기

	CubeShader.use();
	CubeShader.setInt("material.diffMap", 0); // 내용물을 GL_TEXTURE0에서 사용함을 알림

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int cubeVAO; // 다른 색을 가지는 오브젝트를 위해 새 VAO를 만듬
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // 0번 포인터에서 폴리곤 좌표 긁고 쉐이더로 전달
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1); // 1번 포인터에서 폴리곤 법선벡터 긁고 쉐이더로 전달
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2); // 2번 포인터에서 텍스쳐 사용좌표 긁고 쉐이더로 전달

	glViewport(0, 0, 800, 600);
	mat4 modelMat, viewMat, projMat;
	vec3 LightPos = vec3(1.2, 1.0, 2.0), LightDir = -LightPos, LightColor;
	while (!glfwWindowShouldClose(window)) {
		CurFrame = Time(); // 반복할 때마다 시간 기록, 프레임 측정으로 움직임 결정
		DelTime = CurFrame - LastFrame; LastFrame = CurFrame;
		processEsc(window);
		processMove(window);
		//----------
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//----------
		glActiveTexture(GL_TEXTURE0); // 텍스쳐 내용물은 바인딩으로 넘겨줌
		glBindTexture(GL_TEXTURE_2D, texture);
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
		CubeShader.setVec3("light.pos", camPos); // 광원 위치, camPos 해도 됨
		CubeShader.setVec3("light.dir", camTarg); // 광원(손전등) 방향, camTarg 해도 됨
		CubeShader.setVec3("camPos", camPos); // 카메라 위치

		CubeShader.setVec3("light.ambCof", vec3(0.2)); // 반사 계수들
		CubeShader.setVec3("light.diffCof", vec3(0.5));
		CubeShader.setVec3("light.specCof", vec3(1.0));
		CubeShader.setVec3("material.specCof", vec3(0.5, 0.5, 0.5));

		CubeShader.setFloat("material.alpha", 32.0);
		CubeShader.setFloat("light.A", 0.032);
		CubeShader.setFloat("light.B", 0.09);
		CubeShader.setFloat("light.C", 1.0); 
		CubeShader.setFloat("light.Cutoff", cos(Rad(12.5)));
		CubeShader.setFloat("light.outCutoff", cos(Rad(17.5)));

		CubeShader.setMat4("viewMat", viewMat);
		CubeShader.setMat4("projMat", projMat);
		
		glBindVertexArray(cubeVAO);
		for (int i = 0; i < 10; i++) {
			modelMat = mat4(1.0);
			modelMat = translate(modelMat, cubePos[i]);
			modelMat = rotate(modelMat, radians(i*20.0f), vec3(1.0, 0.3*i, 0.5));
			CubeShader.setMat4("modelMat", modelMat);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//--------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
