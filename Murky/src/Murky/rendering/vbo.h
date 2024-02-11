#ifndef MK_VBO_H
#define MK_VBO_H

#include "../core/core.h"

#include <glad/glad.h>

#include "vertex.h"

namespace Murky
{
	class MURKY_API VBO
	{
	public:

		// Vertex Buffer Object ID
		GLuint ID = 0;

		VBO();
		VBO(std::vector<Vertex>& vertices);
		VBO(std::vector<Vertex_PNC>& vertices);

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void) const;

		void SetVBO_Vertex(std::vector<Vertex>& vertices);
		void SetVBO_Vertex_PSC(std::vector<Vertex_PNC>& vertices);
	};
}

#endif