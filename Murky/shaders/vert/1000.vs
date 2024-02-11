layout (location = 0) in vec3 aPos;

// Camera Matrices
uniform mat4 view;
uniform mat4 projection;

// Mesh matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

out vec3 FragPos;

void main()
{
    FragPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
} 