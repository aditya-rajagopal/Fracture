#include "frpch.h"

#include "Application.h"

#include <glad/glad.h>

namespace Fracture {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
		m_Window->SetEventCallback(FRACTURE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray); // generate a vertex array object and store its unique ID in m_VertexArray
		glBindVertexArray(m_VertexArray); // bind the vertex array object to the OpenGL context. This means that all subsequent OpenGL calls will affect the vertex array object we just created.

		// Vertex Buffer
		glGenBuffers(1, &m_VertexBuffer); // generate a vertex buffer object and store its unique ID in m_VertexBuffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer); // bind the vertex buffer object to the OpenGL context. This means that all subsequent OpenGL calls will affect the vertex buffer object we just created.

		// We define a triangle in normalized device coordinates (NDC). NDC is a 3D coordinate system that is normalized so that the visible display area is mapped to [-1, 1] on all 3 axes. 
		// The center of the screen is mapped to (0, 0, 0). Any vertex that falls outside the visible region will be clipped.
		// Here this triangle is defined in the XY plane with Z = 0. The vertices are defined in counter-clockwise order. This means that the triangle will be facing the camera if the camera is looking towards the -Z direction.
		// the direction of the normal follows the right hand thumb rule. If you point your right thumb in the direction of the vertices (from vertex 1 to vertex 2) then the direction of the normal will be the direction of your curled fingers.
		float vertices[3 * 3] = { -0.5f, -0.5f, 0.0f, // first vertex (left bottom)
								   0.5f, -0.5f, 0.0f, // second vertex (right bottom)
								   0.0f,  0.5f, 0.0f }; // third vertex (top center)

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// copy the vertex data into the buffer's memory by calling glBufferData with the vertex buffer object bound to GL_ARRAY_BUFFER. The fourth argument specifies how we want the graphics card to manage the given data. We have 3 options:
																					// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
																					// GL_DYNAMIC_DRAW: the data is likely to change a lot.
																					// GL_STREAM_DRAW: the data will change every time it is drawn.
																					// We want to draw the triangle only once, so we'll use GL_STATIC_DRAW.

		// openGL only sees the above data as a bunch of bytes. We need to tell openGL how it should interpret the vertex data before rendering. We do this by using glVertexAttribPointer.
		glEnableVertexAttribArray(0); // This says we enable the attrib index 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // This says how the data is layed out in the buffer
																					// 0 is the index of the attribute we want to configure. In the previous line we enabled this index with glEnableVertexAttribArray.
																					// 3 specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
																					// GL_FLOAT specifies the type of the data.
																					// GL_FALSE specifies if we want the data to be normalized. If we set this to GL_TRUE all the data that has a value not between 0 (or -1 for signed data) and 1 will be mapped to those values. This is usually not desired but it can be useful when we store colors as unsigned chars (values between 0 and 255) and we want them to be floats between 0 and 1 (which we do).
																					// 3 * sizeof(float) is the stride. It defines where the next vertex attribute would be 
																					// nullptr is the offset of where the position data begins in the buffer. Since the position data is at the start of the data array this value is 0.


		// Index Buffer
		glGenBuffers(1, &m_IndexBuffer); // generate a index buffer object and store its unique ID in m_IndexBuffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer); // bind the index buffer object to the OpenGL context. This means that all subsequent OpenGL calls will affect the index buffer object we just created.
		uint32_t indices[3] = { 0, 1, 2 }; // the indices of the vertices that make up the triangle. As mentioned above we draw the triangle by drawing 3 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // copy the index data into the buffer's memory by calling glBufferData with the index buffer object bound to GL_ELEMENT_ARRAY_BUFFER. We use GL_STATIC_DRAW because the index data will not change.
		// the index buffer does not need a attribute array. It is only used to specify the order in which the vertices should be drawn. This means that we don't need to call glEnableVertexAttribArray and glVertexAttribPointer.
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(FRACTURE_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event); // here we do (*--it) because we want to call the OnEvent function of the layer and not the iterator. The -- is needed because the end iterator is not valid we need 1 before that.
			if (event.Handled) // if the event is handled we break the loop because the layer that set handled=true is a blocking layer
			{
				break;
			}
		}
	}

	void Application::Run()
	{
		//FR_BEGIN_PROFILE_SESSION("Runtime", "../Logs/FractureProfile-Runtime.json");
		while (m_Running)
		{
			static uint32_t frameCount = 0;

			//std::string profile_name = "Fracture::Application::Run() Frame " + std::to_string(frameCount);
			// TODO : The scops are not working correctly.
			//FR_PROFILE_SCOPE(profile_name.c_str());

			{ // Rendering
				//FR_PROFILE_SCOPE("Rendering Colour");
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // debug clear color
				glClear(GL_COLOR_BUFFER_BIT);

				glBindVertexArray(m_VertexArray); // bind the vertex array object
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr); // draw the triangle
				// GL_TRIANGLES specifies the mode we want to draw in. Other modes include GL_POINTS and GL_LINES.
				// 3 specifies the number of indices we want to draw.
				// GL_UNSIGNED_INT specifies the type of the indices.
				// nullptr is the offset of where the index data begins in the buffer. Since the index data is at the start of the data array this value is 0.

				// we dont need to provide a pointer because we are using the indexbuffer that we bound earlier attached to m_vertexArray. This means that OpenGL already knows where the index buffer is.
				// This is because we bound the index buffer to the vertex array object. This also means that we don't need to bind the index buffer every time we want to draw something. As long as we have the vertex array object bound we can just call glDrawElements and OpenGL will know which index buffer to use.
			}

			{ // Layer updates
				//FR_PROFILE_SCOPE("LayerStack::OnUpdate");
				// Call the OnUpdate function of all the layers
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}
			}

			{ // ImGui rendering
				//FR_PROFILE_SCOPE("ImGuiLayer::Rendering");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			{ // Window updates
				//FR_PROFILE_SCOPE("Window::OnUpdate");
				// Call the OnUpdate function of the window
				m_Window->OnUpdate();
			}

			frameCount++;
		}
		//FR_END_PROFILE_SESSION();
	}


}