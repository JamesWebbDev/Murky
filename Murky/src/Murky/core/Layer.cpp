#include "mkpch.h"

#include "Layer.h"

namespace Murky
{
	Layer::Layer(const std::string& name) :
		m_debugName(name)
	{}
	Layer::~Layer()
	{
	}
	void Layer::OnAttach()
	{
		MK_ENG_INFO("Called default OnAttach() in Layer -> {0}!", m_debugName.c_str());
	}
	void Layer::OnDetach()
	{
		MK_ENG_INFO("Called default OnDetach() in Layer -> {0}!", m_debugName.c_str());
	}
	void Layer::OnUpdate()
	{
		MK_ENG_INFO("Called default OnUpdate() in Layer -> {0}!", m_debugName.c_str());
	}
	void Layer::OnEvent()
	{
		MK_ENG_INFO("Called default OnEvent() in Layer -> {0}!", m_debugName.c_str());
	}
}