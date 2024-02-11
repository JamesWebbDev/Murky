layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Camera Matrices
uniform mat4 view;
uniform mat4 projection;

// Mesh matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	mat4 fullModel = model * translation * -rotation * scale;
    FragPos = vec3(fullModel * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(fullModel))) * aNormal;
	// Alter tex coords to match because of differing gltf standards
	TexCoords = mat2(0.0, -1.0, 1.0, 0.0) * aTexCoords;
	
	gl_Position = projection * view * vec4(FragPos, 1.0);
} 