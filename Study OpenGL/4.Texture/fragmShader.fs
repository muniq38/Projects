
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
out vec4 FragColor;
uniform sampler2D ourTexture; // 본체에서 자동으로 할당받음
void main(){
	//FragColor = vec4(vertexColor, 1.0);
	FragColor = texture(ourTexture, texCoord) * vec4(vertexColor, 1.0);
	//ourTexture에서 텍스쳐 받고, TexCoord 모양대로 자르기
}