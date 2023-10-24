#pragma once

#include "Fracture/Core/Layer.h"
#include "Fracture\Events\KeyEvent.h"
#include "Fracture\Events\MouseEvent.h"
#include "Fracture\Events\ApplicationEvent.h"

namespace Fracture {

	class FRACTURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;

	};

}
