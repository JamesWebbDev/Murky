struct Material {
	float shininess;
	vec3 color;
};

uniform Material material;

in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(material.color, 1.0);
}