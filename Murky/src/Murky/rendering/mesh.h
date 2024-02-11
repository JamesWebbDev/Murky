#ifndef MK_MESH_H
#define MK_MESH_H

#include <glad/glad.h>

#include "vertex.h"
#include "vao.h"
#include "material.h"

#include "quaternion.hpp"

#include <bitset>

namespace Murky
{
	class Shader;

	class MURKY_API Mesh
	{
	public:
		Mesh(std::vector<Vertex>& vertices,
			std::vector<GLuint>& indices,
			Material& textures);
		~Mesh();

		std::vector<Vertex> Vertices;
		std::vector<GLuint> Indices;
		Material Mat;

		VAO VAO;



		void Draw
		(
			const Shader& shader,
			glm::mat4 matrix = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

		static void Static_Draw
		(
			Mesh& mesh,
			const Shader& shader,
			glm::mat4 matrix = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

		static inline std::bitset<4> GetVarFlags(Vertex v)
		{
			std::bitset<4> flags;

			flags.set(0, true); // Position

			if (v.Normal != glm::vec3(FLT_MAX)) { flags.set(1); } // Normal
			if (v.Tangent != glm::vec4(FLT_MAX)) { flags.set(2); } // Tangent
			if (v.TexCoords != glm::vec2(FLT_MAX)) { flags.set(3); } // Texture Coords

			return flags;
		}
	};
}

#endif