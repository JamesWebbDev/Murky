#include "mkpch.h"

#include "rbo.h"

namespace Murky
{
	Murky::RBO::RBO(int32_t width, int32_t height)
	{
		glGenRenderbuffers(1, &m_id);

		Bind();

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		Unbind();
	}

	void Murky::RBO::Bind(void) const { glBindRenderbuffer(GL_RENDERBUFFER, m_id); }

	void Murky::RBO::Unbind(void) const { glBindRenderbuffer(GL_RENDERBUFFER, 0); }

	void Murky::RBO::Delete(void) { glDeleteRenderbuffers(1, &m_id); m_id = 0; }

}