
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // 각도계산을 위해 법선벡터 제공받음

// 세 가지 변환행렬
uniform mat4 projMat; // 원근법 투영 
uniform mat4 viewMat; // 카메라 동작과 시야조절
uniform mat4 modelMat; // 폴리곤을 공간에 배치

out vec3 Normal;
out vec3 FragPos; // 픽셀쉐이더에 넘겨줄 인자들

void main(){
	gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0); 
	// aPos가 인접한 model, view, proj 순서대로 변환됨
	Normal = mat3(transpose(inverse(modelMat))) * aNormal; // 받은 법선벡터 넘겨줌
	// model에 의해 형태가 바뀌게 되면 수직성이 깨짐 -> model의 역행렬을 처리함으로 복원
	FragPos = vec3(modelMat * vec4(aPos, 1.0)); // 폴리곤 위치
}