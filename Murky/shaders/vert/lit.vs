layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Camera Matrices
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	// cast the matrix to a 3x3 matrix to ensure it loses 
	// its translation properties and that it can multiply 
	// with the vec3 normal vector
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;
} 