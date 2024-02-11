struct Material {
	
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	vec3 color;
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec4 Tangent;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    FragColor = vec4(material.color * vec3(texture(material.diffuse, TexCoords)), 1.0);
}