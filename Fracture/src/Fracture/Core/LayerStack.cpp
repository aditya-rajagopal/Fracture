#include "frpch.h"

#include "LayerStack.h"


namespace Fracture {
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
	}

	void LayerStack::PushLayer(Layer* Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, Layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* Layer)
	{
		m_Layers.emplace_back(Layer);
	}

	void LayerStack::PopLayer(Layer* Layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* Layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), Layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}
