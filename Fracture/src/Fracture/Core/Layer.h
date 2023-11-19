#pragma once

#include "Fracture\Core\Core.h"
#include "Fracture\Events\Event.h"

#include "Fracture\Utils\Timestep.h"

namespace Fracture
{
	class FRACTURE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep delta_time) {};
		virtual void OnEvent(Event& event) {};
		virtual void OnImGuiRender() {};

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

} // namespace Fracture

