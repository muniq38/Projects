
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 vertexColor;
out vec2 texCoord;
uniform mat4 transform; // 변환행렬로 사용됨

void main(){
	vertexColor = aColor;
	texCoord = aTex;
	gl_Position = transform * vec4(aPos, 1.0); 
	// aPos가 transform에 저장된 대로 변환됨
}