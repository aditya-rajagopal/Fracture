#pragma once
/*!
* @file LayerStack.h
* @brief LayerStack header file Contains the LayerStack class that is used to store all the layers that are currently active.
* 
* @see Layer
* @see LayerStack
* @see Application
* 
* @author Aditya Rajagopal
*/

#include "frpch.h"
#include "Fracture\Core\Core.h"
#include "Layer.h"


namespace Fracture {

	/*!
	* @brief The LayerStack class is used to store all the layers that are currently active.
	* 
	* @details The LayerStack class is used to store all the layers that are currently active.
	* The layers are stored in a vector of Layer pointers. 
	* The layers are stored in the first half of the vector and the overlays are stored in the second half of the vector. The demarcation between the layers and the overlays is stored in the m_LayerInsertIndex variable.
	* 
	* @see Layer
	*/
	class FRACTURE_API LayerStack
	{
	public:
		LayerStack(); /// Constructor

		/*!
		* @brief Destructor of the LayerStack class. This will detach all the layers from the layer stack and delete them.
		* 
		* @todo: Should we return the pointer to the layer instead of deleting it for the application to handle?
		*/
		~LayerStack(); 

		/*!
		* @brief Function that will attach a layer to the layer stack.
		* 
		* @details The function will attach a layer to the layer stack. The layer will be added to the first half of the layer stack.
		* 
		* @see Layer
		* 
		* @param[in] Layer* layer: The layer to be attached to the layer stack.
		*/
		void PushLayer(Layer* layer);

		/*!
		* @brief Function that will attach an overlay to the layer stack.
		* 
		* @details The function will attach an overlay to the layer stack. The overlay will be emplaced to the back of the layer stack.
		* 
		* @see Layer
		* 
		* @param[in] Layer* layer: The overlay to be attached to the layer stack at the back.
		*/
		void PushOverlay(Layer* layer);

		/*!
		* @brief Function that will detach a layer from the layer stack.
		* 
		* @details Here we will find the layer in the layer stack call its Layer::OnDetach function and erase it from the LayerStack.
		* 
		* @see Layer
		* 
		* @todo: Should we return the pointer to the layer after detaching it?
		* 
		* @param[in] Layer* layer: The layer to be detached from the layer stack.
		*/
		void PopLayer(Layer* layer);

		/*!
		* @brief Function that will detach an overlay from the layer stack.
		* 
		* @details Here we will find the overlay in the layer stack call its Layer::OnDetach function and erase it from the LayerStack.
		* 
		* @see Layer
		* 
		* @todo: Should we return the pointer to the layer after detaching it?
		* 
		* @param[in] Layer* layer: The overlay to be detached from the layer stack.
		*/
		void PopOverlay(Layer* layer);

		/*!
		* @brief create an iterator to the beginning of the layer stack.
		* 
		* @return std::vector<Layer*>::iterator: An iterator to the beginning of the layer stack.
		*/
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		/*!
		* @brief create an iterator to the end of the layer stack.
		* 
		* @return std::vector<Layer*>::iterator: An iterator to the end of the layer stack.
		*/
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers; /// The vector of Layer pointers that will hold the layers
		uint32_t m_LayerInsertIndex = 0; /// The current index in the layer stack where a Layer will be inserted (not an overlay)
	};
}
