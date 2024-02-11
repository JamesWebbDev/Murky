#ifndef MK_LAYER_STACK_H
#define MK_LAYER_STACK_H

#include "../core/core.h"

#include "Layer.h"

namespace Murky
{
	typedef std::vector<Layer*> LayerVec;
	typedef std::vector<Layer*>::iterator LayerVecIt;

	class MURKY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		Layer* PushLayer(Layer* layer);
		Layer* PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);


		LayerVecIt begin() { return m_layers.begin(); }
		LayerVecIt end() { return m_layers.end(); }
	private:

		LayerVec m_layers;
		// Pointer to start of overlay layers in vector
		LayerVecIt m_layerInsert; 
	};
}

#endif