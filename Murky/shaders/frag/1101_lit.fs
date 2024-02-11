struct Material {
	
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	vec3 color;
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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir); 

void main()
{
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 normal = normalize(Normal);
	vec3 result = vec3(0.0);

	// -------- Directional Lighting --------
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
		result += CalcDirLight(dirLights[i], normal, viewDir);

    FragColor = vec4(material.color * result, 1.0);
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