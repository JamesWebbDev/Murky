#ifndef RBO_H
#define RBO_H

#include "../core/core.h"

#include <glm.hpp>
#include <glad/glad.h>

namespace Murky
{
	class MURKY_API RBO // Render Buffer Object (stores depth and stencil buffers)
	{
	public:

		RBO() {}
		RBO(int32_t width, int32_t height);

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void);

		inline GLuint GetID() const { return m_id; }

	private:
		GLuint m_id = 0;
	};
}

#endif