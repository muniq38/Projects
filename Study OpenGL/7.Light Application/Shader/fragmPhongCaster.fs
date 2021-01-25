
#version 330 core
out vec4 FragColor;

in vec3 Normal; // 폴리곤 법선벡터
in vec3 FragPos; // 폴리곤 위치
in vec2 texCoord; // 텍스쳐 좌표
vec3 Norm, Light, Reflect, View; // 법선, 입사광, 반사광, 시선의 방향
float dist, attenu;
float theta, eps, intensity;

struct Material{ // 재질의 상태를 정의하는 구조체
	sampler2D diffMap;
	vec3 specCof;
	float alpha;
};

struct LightSource{ // 빛의 상태를 정의하는 구조체
	vec3 ambCof;
	vec3 diffCof;
	vec3 specCof;
	vec3 pos; vec3 dir; // 광원 위치와 방향(for flashlight)

	float A, B, C; // 2차 다항식의 계수 - for attenuation
	float Cutoff, outCutoff; // for soft edges, 빛이 나가는 중심각의 cosine값
};

// 빛과 광원 처리는 모두 픽셀쉐이더에서 담당
uniform vec3 camPos; // 카메라의 위치 
uniform Material material; // 재질의 상태
uniform LightSource light; // 빛의 상태

void main(){
	// 여러가지 방향벡터 추출하기
	Norm = normalize(Normal); Light = normalize(light.pos - FragPos); // 법선과 입사광
	View = normalize(camPos - FragPos); // 시선
	Reflect = reflect(-Light, Norm); // 반사광 (입사광의 대칭)
	dist = length(light.pos - FragPos); 
	attenu = 1.0 / ( light.A*(dist*dist) + light.B*(dist) + light.C ); // 2차함수의 역수로 표현되는 감쇠효과

    // Ambient(주변광) 계산
	vec3 ambient = light.ambCof * vec3(texture(material.diffMap, texCoord)); 
	
	// Diffuse(확산난반사) 계산
	float cos = max(dot(Norm, Light), 0.0); // 입사광이 법선 방향에 가까울수록 더 밝아짐 (cosine)
	vec3 diffuse = cos * light.diffCof * vec3(texture(material.diffMap, texCoord)); 

	// Specular(정반사광) 계산
	float cosexp = pow(max(dot(View, Reflect), 0.0), material.alpha); 
	// 시선과 반사광이 일치할수록 광택이 잘 보임. 광택효과의 극대화를 위해 지수함수 사용 
	vec3 specular = cosexp * material.specCof;

	// 부드러운 손전등 효과 구현, 내부원뿔 - 경계원뿔(그라데이션) - 외부 구조
	theta = dot(Light, normalize(-light.dir)); // 광선과 손전등 방향의 각에 따라 그라데이션 표현 여부 달라짐
	eps = (light.Cutoff - light.outCutoff); 
	intensity = clamp((theta-light.outCutoff) / eps, 0.0, 1.0); // 내부원뿔에서 1.0, 외부에서 0.0

	// 최종 휘도 계산
	vec3 result = ambient + intensity * (diffuse + specular); 
	FragColor = vec4(attenu * result, 1.0); 
}