#include "mkpch.h"

#include "gl_wrapper.h"

namespace Murky::MurkyGL
{
	void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glClearColor(r, g, b, a);
	}
	void ClearBuffers_COLOR_DEPTH()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void ClearBuffers_COLOR()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void ClearBuffers_DEPTH()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	void Enable(GLenum id)
	{
		glEnable(id);
	}
}