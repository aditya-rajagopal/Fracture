#pragma once
/*!
* @file Layer.h
* @brief Layer header file. Contains the Layer class.
* 
* @see Layer
* @see LayerStack
* @see Application
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Core\Core.h"
#include "Fracture\Events\Event.h"

#include "Fracture\Utils\Helpers.h"

namespace Fracture
{
	/*!
	* @brief The Layer class is the base class for all layers in the engine. Layers are used to separate different parts of the application and set an order of execution.
	* 
	* @see LayerStack
	*/
	class FRACTURE_API Layer
	{
	public:
		/*!
		* @brief Layer constructor. Currently only stores the name of the layer for debugging purposes.
		* 
		* @param[in] const std::string& name: The name of the layer.
		*/
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		/*!
		* @brief Called when the layer is attached to the layer stack.
		*/
		virtual void OnAttach() {};

		/*!
		* @brief Called when the layer is detached from the layer stack.
		*/
		virtual void OnDetach() {};

		/*!
		* @brief Function called every frame by the application.
		* 
		* @param[in] Timestep delta_time: The time passed since the last frame
		*/
		virtual void OnUpdate(Utils::Timestep delta_time) {};

		/*!
		* @brief the function called by the application OnEvent function for each layer in the layerstack with the current event being handled.
		* 
		* @see Application::OnEvent
		* @see Event
		* 
		* @param[in] Event& event: The event being handled.
		*/
		virtual void OnEvent(Event& event) {};

		/*!
		* @brief Function called every frame by the application for rendering ImGui elements.
		* 
		* @see ImGui
		*/
		virtual void OnImGuiRender() {};

		/*!
		* @brief Getter for the name of the layer. Mostly used for debugging purposes.
		* 
		* @return const std::string&: The name of the layer.
		*/
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; /// The name of the layer
	};

} // namespace Fracture

