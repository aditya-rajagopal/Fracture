#pragma once

#include "frpch.h"
#include "Fracture\Core\Core.h"
#include "Layer.h"


namespace Fracture {
	class FRACTURE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Layer);
		void PopLayer(Layer* Layer);
		void PopOverlay(Layer* Layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};
}
