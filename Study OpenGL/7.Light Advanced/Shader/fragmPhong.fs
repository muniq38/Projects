
#version 330 core
out vec4 FragColor;

struct Material{ // 재질의 상태를 정의하는 구조체
	vec3 ambCof;
	vec3 diffCof;
	vec3 specCof;
	float alpha;
};

struct LightSource{ // 빛의 상태를 정의하는 구조체
	vec3 ambCof;
	vec3 diffCof;
	vec3 specCof;
	vec3 pos;
};

in vec3 Normal; // 폴리곤 법선벡터
in vec3 FragPos; // 폴리곤 위치
vec3 Norm, Light, Reflect, View; // 법선, 입사광, 반사광, 시선의 방향

// 빛과 광원 처리는 모두 픽셀쉐이더에서 담당
uniform vec3 camPos; // 카메라의 위치 
uniform Material material; // 재질의 상태
uniform LightSource light; // 빛의 상태

void main(){
	// 여러가지 방향벡터 추출하기
	Norm = normalize(Normal); Light = normalize(light.pos - FragPos); // 법선과 입사광
	View = normalize(camPos - FragPos); // 시선
	Reflect = reflect(-Light, Norm); // 반사광 (입사광의 대칭)

    // Ambient(주변광) 계산
	vec3 ambient = material.ambCof * light.ambCof; 
	
	// Diffuse(확산난반사) 계산
	float cos = max(dot(Norm, Light), 0.0); // 입사광이 법선 방향에 가까울수록 더 밝아짐 (cosine)
	vec3 diffuse = cos * material.diffCof * light.diffCof; 

	// Specular(정반사광) 계산
	float cosexp = pow(max(dot(View, Reflect), 0.0), material.alpha); 
	// 시선과 반사광이 일치할수록 광택이 잘 보임. 광택효과의 극대화를 위해 지수함수 사용 
	vec3 specular = cosexp * material.specCof;

	// 최종 휘도 계산
	vec3 result = ambient + diffuse + specular; 
	FragColor = vec4(result, 1.0); // 반사되는 색은 물체의 색과 빛을 곱한것
}