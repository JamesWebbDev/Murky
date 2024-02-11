
struct Material {
	
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};


uniform Material material;

struct DirLight {

	vec3 direction;
	
	vec3 colour;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//#define NR_DIR_LIGHTS 1 , <-- defined in c++ shader
uniform DirLight dirLights[NR_DIR_LIGHTS];

struct PointLight {    
    vec3 position;
	
	vec3 colour;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
//#define NR_POINT_LIGHTS 4 , <-- defined in c++ shader
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct Light {
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
    // Directional/Spot Light
	vec3 direction;

	// Point/Spot Light
	vec3 position; 
	
	// Point Light
	float constant;
	float linear;
	float quadratic;
	
	// Spot Light
	float innerCutOff;
	float outerCutOff;
};

uniform Light light;

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir); 
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

void main()
{
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = vec3(0.0);

    // -------- Directional Lighting --------
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
		result += CalcDirLight(dirLights[i], norm, viewDir);
    //     -------- Point Lights --------
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    //     -------- Spot Light --------
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return light.colour * (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return light.colour * (ambient + diffuse + specular);
}