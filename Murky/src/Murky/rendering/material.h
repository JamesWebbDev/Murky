#ifndef MK_MATERIAL_H
#define MK_MATERIAL_H

#include "texture2d.h"
#include "shader.h"

#include <glm.hpp>

namespace Murky
{
	class MURKY_API Material
	{
	public:

		std::vector<Texture2D> Textures;

		float shininess = 32.0f;
		glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);

		Material()
		{}

		void ApplyAttributesToShader(const Shader& shader);
		void BindTextures();
	};
}

#endif