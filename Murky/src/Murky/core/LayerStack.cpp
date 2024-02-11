#include "mkpch.h"

#include "LayerStack.h"

namespace Murky
{
	LayerStack::LayerStack()
	{
		m_layerInsert = m_layers.begin();
	}
	LayerStack::~LayerStack()
	{
		// Tie Layer lifetime to application
		/// TODO: Update this to per scene later
		for (Layer* layer : m_layers)
		{
			delete layer;
		}
	}
	Layer* LayerStack::PushLayer(Layer* layer)
	{
		m_layerInsert = m_layers.emplace(m_layerInsert, layer);
		return layer;
	}
	Layer* LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
		return overlay;
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		LayerVecIt it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			// Found layer to erase!
			m_layers.erase(it);
			m_layerInsert--;
		}
		else
		{
			MK_ENG_WARN("Couldn't find layer in stack to pop -> {0}!", layer->GetName().c_str());
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		LayerVecIt it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			// Found layer to erase!
			m_layers.erase(it);
		}
		else
		{
			MK_ENG_WARN("Couldn't find overlay in stack to pop -> {0}!", overlay->GetName().c_str());
		}
	}
}