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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};
}
