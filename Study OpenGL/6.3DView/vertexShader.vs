
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoord;
uniform mat4 projMat; // 세 가지 변환행렬
uniform mat4 viewMat;
uniform mat4 modelMat;

void main(){
	texCoord = aTex;
	gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0); 
	// aPos가 인접한 model, view, proj 순서대로 변환됨
}