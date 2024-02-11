#ifndef MK_LAYER_H
#define MK_LAYER_H

#include "../core/core.h"

namespace Murky
{
	class MURKY_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent();

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;

	};
}

#endif