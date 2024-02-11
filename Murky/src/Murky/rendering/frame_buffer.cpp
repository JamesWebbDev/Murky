#include "mkpch.h"

#include "frame_buffer.h"
#include <glad/glad.h>

namespace Murky
{
	FrameBuffer::FrameBuffer(int32_t width, int32_t height)
	{
		m_width = width;
		m_height = height;

		if (m_fbo.get() != NULL && m_fbo->GetID())
		{
			Delete();
		}

		m_fbo = std::make_unique<FBO>();
		m_fbo->Bind();

		// Initialise Frame Buffer Object
		// Create Texture for colour
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		// Define Texture attributes
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		m_fbo->AttachTexture(GL_COLOR_ATTACHMENT0, m_texId);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_rbo = std::make_unique<RBO>(width, height);
		m_fbo->AttachRenderBuffer(m_rbo->GetID());

		GLenum fboStatus = m_fbo->GetStatus();
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		{
			MK_ENG_ERROR("Framebuffer error : {0}", fboStatus);
		}

		// Draw buffers using texture from m_texId
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(m_texId, buffers);
		m_fbo->Unbind();
	}
	void FrameBuffer::GetWidthAndHeight(int32_t& inWidth, int32_t& inHeight) const
	{
		inWidth = m_width;
		inHeight = m_height;
	}
	void FrameBuffer::Bind(void) const
	{
		m_fbo->Bind();
		m_rbo->Bind();

		glViewport(0, 0, m_width, m_height);
		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void FrameBuffer::Unbind(void) const
	{
		m_fbo->Unbind();
		m_rbo->Unbind();
	}
	void FrameBuffer::Delete(void)
	{
		if (m_fbo.get() != NULL && m_fbo->GetID())
		{
			m_fbo->Delete();
			m_fbo.release();
			m_rbo->Delete();
			m_rbo.release();
			glDeleteTextures(1, &m_texId);
			m_texId = 0;
		}
	}
}