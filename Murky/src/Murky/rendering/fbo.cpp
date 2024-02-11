#include "mkpch.h"

#include "fbo.h"

namespace Murky
{
	FBO::FBO(void)
	{
		glGenFramebuffers(1, &m_id);
	}
	void FBO::AttachTexture(GLuint glAttachment, GLuint textureId) const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachment, GL_TEXTURE_2D, textureId, 0);
	}

	void FBO::AttachRenderBuffer(GLuint renderbufferId) const
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbufferId);
	}

	GLenum FBO::GetStatus()
	{
		Bind();
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		Unbind();
		return status;
	}

	void Murky::FBO::Bind(void) const { glBindFramebuffer(GL_FRAMEBUFFER, m_id); }

	void Murky::FBO::Unbind(void) const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	void Murky::FBO::Delete(void) { glDeleteFramebuffers(1, &m_id); m_id = 0; }
}