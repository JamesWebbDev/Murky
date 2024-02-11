#ifndef MK_RENDER_CONTEXT_H
#define MK_RENDER_CONTEXT_H

#include "../core/core.h"

namespace Murky
{
	class MURKY_API RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void PreRender() = 0;
		virtual void PostRender() = 0;
	};
}

#endif