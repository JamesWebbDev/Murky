#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "fbo.h"
#include "rbo.h"

namespace Murky
{
	class MURKY_API FrameBuffer // Frame Buffer Object
	{
	public:
		FrameBuffer() {}
		FrameBuffer(int32_t width, int32_t height);

		void GetWidthAndHeight(int32_t& inWidth, int32_t& inHeight) const;

		void Bind(void) const;
		void Unbind(void) const;
		void Delete(void);

		inline GLuint GetTextureID() const { return m_texId; }
	private:

		std::unique_ptr<FBO> m_fbo;
		std::unique_ptr<RBO> m_rbo;
		GLuint m_texId = 0;


		int32_t m_width = 0, m_height = 0;
	};
}

#endif