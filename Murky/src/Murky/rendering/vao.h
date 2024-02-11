#ifndef MK_VAO_H
#define MK_VAO_H

#include "vbo.h"

namespace Murky
{
	class MURKY_API VAO
	{
	public:

		// Vertex Array Object ID
		GLuint ID = 0;

		VAO(void);

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void) const;
	};
}

#endif