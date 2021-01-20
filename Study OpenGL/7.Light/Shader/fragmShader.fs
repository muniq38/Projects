
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor; // 아예 빛 관련 요소를 여기에서 받아버림
uniform vec3 lightColor; // 기존에는 layout in을 통해 제공받았음

void main(){
	FragColor = vec4(objectColor * lightColor, 1.0);
	// 반사되는 색은 물체의 색과 빛의 내적
}