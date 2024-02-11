#ifndef MK_VERTEX_H
#define MK_VERTEX_H

#include <glm.hpp>

namespace Murky
{
	MURKY_API typedef struct
	{
	public:
		glm::vec3 Position, Normal;
		glm::vec4 Tangent;
		glm::vec2 TexCoords;
	} Vertex;

	MURKY_API typedef struct
	{
		glm::vec3 Position, Normal;
		glm::vec2 TexCoords;
	} Vertex_PNC;
}

#endif