#version 330 core
#define NR_POINT_LIGHTS 8

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;
//in vec2 TexCoords;

struct Direction {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;      
	float outerCutOff; 

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 viewPos;
uniform vec3 objectColor;
//uniform sampler2D ourTexture;

uniform Direction dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform sampler2D shadowMap;

vec3 CalcDirLight(Direction light, vec3 normal, vec3 viewDir, float shadow);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lightDir = normalize(-dirLight.direction);
    float shadow = ShadowCalculation(FragPosLightSpace, norm, lightDir);

	vec3 result = CalcDirLight(dirLight, norm, viewDir, shadow);

	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

	FragColor = vec4(result * objectColor, 1.0);
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    projCoords = projCoords * 0.5 + 0.5;

    if(projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    
    float currentDepth = projCoords.z;

    float bias = 0.005; 
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

vec3 CalcDirLight(Direction light, vec3 normal, vec3 viewDir, float shadow) {
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec3 ambient = light.ambient;
	vec3 diffuse = light.diffuse * diff;
	vec3 specular = light.specular * spec;
	return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	if (light.constant < 0.001) return vec3(0.0);
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * attenuation;
	vec3 diffuse = light.diffuse * diff * attenuation;
	vec3 specular = light.specular * spec * attenuation;
	return (ambient + diffuse + specular);
}