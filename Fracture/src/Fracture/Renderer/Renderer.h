#pragma once
/*!
* @file Renderer.h
* @brief Contains the Renderer class. It provides an interface to render a scene.
* 
* @see Renderer
* @see RendererCommand
* @see RendererAPI
* @see OpenGLRendererAPI
* 
* @todo: Add VulkanRendererAPI
* 
* @author Aditya rajagopal
*/

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/RenderCommand.h"
#include "Fracture/Renderer/RendererAPI.h"

#include "Fracture\Renderer\VertexArray.h"
#include "Fracture\Renderer\Shader.h"
#include "Fracture\Renderer\OrthographicCamera.h"

#include <glm/glm.hpp>


namespace Fracture
{
	 /*!
	 * @brief The Renderer class is used to render a scene. It provides an interface to render a scene.
	 */
	class Renderer
	{
	public:
		/*!
		* @brief Function that initializes the renderer. This function is called once application. Currently it only initializes the renderer API.
		*/
		static void Init();

		/*!
		* @brief Function that declares the beginning of a scene. It sets the view projection matrix for the scene from the provided camera.
		* 
		* @todo: Currently only supports orthographic camera. Add support for any camera.
		* 
		* @param[in] OrthographicCamera& camera: The camera that is used to set the view projection matrix.
		*/
		static void BeginScene(OrthographicCamera& camera);

		/*!
		* @brief Function that declares the end of a scene. Currently does nothing.
		*/
		static void EndScene();
		
		/*!
		* @brief The OnWindowResize function is called when the window is resized. It sets the viewport of the renderer API to the new window size.
		* 
		* @param[in] uint32_t width: The new width of the window.
		* @param[in] uint32_t height: The new height of the window.
		*/
		static void OnWindowResize(uint32_t width, uint32_t height);


		/*!
		* @brief Function that submits a vertex array, shader, and transform to the renderer API. Sets the shader uniforms and does a draw call.
		* 
		* @details The shader uniforms for the view projection matrix and the model matrix are set. The draw call is done using the current renderer API.
		* 
		* @todo: Add support for materails.
		* @todo: Add support for batch rendering.
		* @todo: Add support for instanced rendering.
		* 
		* @param[in] const Ref<VertexArray>& vertexArray: Pointer to the vertex array to submit.
		* @param[in] const Ref<Shader>& shader: Pointer to the shader to submit.
		* @param[in] const glm::mat4& transform: The transform to submit (model matrix).
		*/
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform);

		/*!
		* @brief Function that returns the current renderer API.
		* 
		* return RendererAPI::API: The current renderer API.
		*/
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		/*!
		* @brief This is a temporary structure that is used to store all the data that is needed to render the current scene.
		* 
		* @todo: Move this to a scene class.
		*/
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix; /// The view projection matrix of the camera that is used to render the scene.
			uint32_t CurrentBoundShader = 0; /// The current shader that is bound to the renderer API.
		};

		static Scope<SceneData> s_SceneData; /// A pointer to the scene data. This is reset everytime begin scene is called.
	};
}