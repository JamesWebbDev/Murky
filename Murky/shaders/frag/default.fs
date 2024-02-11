
struct Material {
	
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	vec3 color;
};

uniform Material material;

out vec4 FragColor;

void main()
{
    FragColor = vec4(material.color, 1.0);
}