
#version 330 core
out vec4 FragColor;

in vec3 Normal; // 폴리곤 법선벡터
in vec3 FragPos; // 폴리곤 위치
in vec2 texCoord; // 텍스쳐 좌표

struct Material{ // 재질의 상태를 정의하는 구조체
	sampler2D diffMap;
	float alpha;
};

struct LightSource{ // 빛의 상태를 정의하는 구조체
	vec3 ambCof;
	vec3 diffCof;
	vec3 specCof;
	vec3 pos; vec3 dir; // 광원 위치와 방향

	float A, B, C; // 2차 다항식의 계수 - for attenuation
	float Cutoff, outCutoff; // for soft edges, 빛이 나가는 중심각의 cosine값
};

#define Count 6

// 빛과 광원 처리는 모두 픽셀쉐이더에서 담당
uniform vec3 camPos; // 카메라의 위치 
uniform Material material; // 재질의 상태
uniform LightSource L[Count]; // 빛의 상태

vec3 CalcLight(LightSource light, vec3 Norm, vec3 View, vec3 FragPos, int mode){
	// mode : 0(Directional), 1(Point), 2(Spotlight)
	vec3 Light, Reflect, Texture;
	float intensity = 1.0, attenu = 1.0;
	if(mode != 0){
		Light = normalize(light.pos - FragPos);
		float dist = length(light.pos - FragPos);
		attenu = 1.0 / ( light.A*(dist*dist) + light.B*(dist) + light.C );
		if(mode == 2){
			float theta = dot(Light, normalize(-light.dir));
			float eps = light.Cutoff - light.outCutoff;
			intensity = clamp((theta-light.outCutoff) / eps, 0.0, 1.0);
		}
	}else Light = normalize(-light.dir);
	Reflect = reflect(-Light, Norm);
	Texture = vec3(texture(material.diffMap, texCoord));
	
	float cos = max(dot(Norm, Light), 0.0);
	float cosexp = pow(max(dot(View, Reflect), 0.0), material.alpha);
	vec3 ambient = light.ambCof * Texture;
	vec3 diffuse = cos * light.diffCof * Texture;
	vec3 specular = cosexp * light.specCof;
	
	return intensity * attenu * (ambient + diffuse + specular);
}// 함수의 내용은 fragmPhongCaster.fs 참고

void main(){
	// 모든 광학 계산과정을 함수로 넘겨서 일반화함
	vec3 Norm = normalize(Normal), View = normalize(camPos - FragPos);

	vec3 result = CalcLight(L[0], Norm, View, FragPos, 0);
	for(int i=1; i<Count-1; i++) result += CalcLight(L[i], Norm, View, FragPos, 1);
	result += CalcLight(L[Count-1], Norm, View, FragPos, 2);

	FragColor = vec4(result, 1.0); // 모든 걸 합친 결과값 제출
}

