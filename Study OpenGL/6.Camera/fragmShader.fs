
#version 330 core

in vec2 texCoord;

out vec4 FragColor;
uniform sampler2D Tex1; // texture 전달받는 곳

void main(){
	//FragColor = vec4(vertexColor, 1.0);
	FragColor = texture(Tex1, texCoord);
	//FragColor = mix(texture(Tex1, texCoord), texture(Tex2, texCoord), 0.4);
}