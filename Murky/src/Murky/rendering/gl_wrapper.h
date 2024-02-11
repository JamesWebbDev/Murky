#ifndef MK_GL_WRAPPER_H
#define MK_GL_WRAPPER_H

#include "../core/core.h"
#include <glad/glad.h>

namespace Murky::MurkyGL
{
	MURKY_API void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	MURKY_API void ClearBuffers_COLOR_DEPTH();
	MURKY_API void ClearBuffers_COLOR();
	MURKY_API void ClearBuffers_DEPTH();
	MURKY_API void Enable(GLenum id);
}

#endif