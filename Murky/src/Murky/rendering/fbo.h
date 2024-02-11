#ifndef MK_FBO_H
#define MK_FBO_H

#include <glad/glad.h>

#include "../core/core.h"

namespace Murky
{
	// Frame Buffer Object (holds drawn colour, depth and stencil buffer data)
	class MURKY_API FBO 
	{
	public:

		FBO(void);

		void AttachTexture(GLuint glAttachment, GLuint textureId) const;
		void AttachRenderBuffer(GLuint renderbufferId) const;

		GLenum GetStatus();

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void);

		inline GLuint GetID() const { return m_id; }

	private:
		GLuint m_id = 0;
	};
}

#endif