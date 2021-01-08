
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float xoffset;
out vec3 vertexColor;
void main(){
	vertexColor = aColor;
	gl_Position = vec4(aPos.x+xoffset, aPos.yz, 1.0);
}