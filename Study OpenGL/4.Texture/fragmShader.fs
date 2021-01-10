
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
out vec4 FragColor;
uniform sampler2D Tex1; // texture 전달받는 곳
uniform sampler2D Tex2; // texture2 전달받는 곳
void main(){
	//FragColor = vec4(vertexColor, 1.0);
	//FragColor = texture(Tex1, texCoord) * vec4(vertexColor, 1.0);
	FragColor = mix(texture(Tex1, texCoord), texture(Tex2, texCoord), 0.4);
	// Tex1과 Tex2 5:5로 혼합
}