
#version 330 core
out vec4 FragColor;

in vec3 Normal; // 폴리곤 법선벡터
in vec3 FragPos; // 폴리곤 위치
vec3 Norm, Light, Reflect, View; // 법선, 입사광, 반사광, 시선의 방향

// 빛과 광원 처리는 모두 픽셀쉐이더에서 담당
uniform vec3 lightPos; // 광원의 위치
uniform vec3 objectColor; // 사물의 색
uniform vec3 lightColor; // 빛의 색
uniform vec3 camPos; // 카메라의 위치 -> Specular 구현할때 쓰임

void main(){
	float ambientCof = 0.2;
	vec3 ambient = ambientCof * lightColor; // Ambient(주변광) 계산
	
	float diffuseCof = 1.0;
	Norm = normalize(Normal); Light = normalize(lightPos - FragPos); // 법선과 입사광의 방향 추출
	float cos = max(dot(Norm, Light), 0.0); // 입사광이 법선 방향에 가까울수록 더 밝아짐 (cosine)
	vec3 diffuse = cos * diffuseCof * lightColor; // Diffuse(확산난반사) 계산

	float specularCof = 1.0, alpha = 32; 
	View = normalize(camPos - FragPos); // 시선의 방향
	Reflect = reflect(-Light, Norm); // 입사광을 법선에 대칭하면 반사광의 방향
	float cosexp = pow(max(dot(View, Reflect), 0.0), alpha); 
	// 시선과 반사광이 일치할수록 광택이 잘 보임. 광택효과의 극대화를 위해 지수함수 사용 
	vec3 specular = cosexp * specularCof * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor; // 최종 휘도 계산
	FragColor = vec4(result, 1.0);
	// 반사되는 색은 물체의 색과 빛을 곱한것
}