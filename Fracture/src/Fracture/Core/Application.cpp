#include "frpch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Fracture\Renderer\Shader.h"
#include "Fracture\Input\Input.h"
#include "Fracture\Input\KeyCodes.h"

namespace Fracture {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float2: return		GL_FLOAT;
			case ShaderDataType::Float: return		GL_FLOAT;
			case ShaderDataType::Float3: return		GL_FLOAT;
			case ShaderDataType::Float4: return		GL_FLOAT;
			case ShaderDataType::Mat3: return		GL_FLOAT;
			case ShaderDataType::Mat4: return		GL_FLOAT;
			case ShaderDataType::Int: return		GL_INT;
			case ShaderDataType::Int2: return		GL_INT;
			case ShaderDataType::Int3: return		GL_INT;
			case ShaderDataType::Int4: return		GL_INT;
			case ShaderDataType::Bool: return		GL_BOOL;
		}

		FR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		FR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
		m_Window->SetEventCallback(FRACTURE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex Array
		m_TriangleVertexArray.reset(VertexArray::Create()); // create a vertex array object (VAO)

		// Vertex Buffer

		// We define a triangle in normalized device coordinates (NDC). NDC is a 3D coordinate system that is normalized so that the visible display area is mapped to [-1, 1] on all 3 axes. 
		// The center of the screen is mapped to (0, 0, 0). Any vertex that falls outside the visible region will be clipped.
		// Here this triangle is defined in the XY plane with Z = 0. The vertices are defined in counter-clockwise order. This means that the triangle will be facing the camera if the camera is looking towards the -Z direction.
		// the direction of the normal follows the right hand thumb rule. If you point your right thumb in the direction of the vertices (from vertex 1 to vertex 2) then the direction of the normal will be the direction of your curled fingers.
		float vertices[3 * 7] = { -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 0.0, // first vertex (left bottom) position, colour
								   0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 0.0, // second vertex (right bottom) position, colour
								   0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0, 0.0 }; // third vertex (top center) position, colour
		
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			// creating the layout in a scope so that it is destroyed after we set it in the vertex buffer
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Colour"}
			};
			m_VertexBuffer->SetLayout(layout);
		}
		m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 }; // the indices of the vertices that make up the triangle. As mentioned above we draw the triangle by drawing 3 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.
		
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);
		m_TriangleVertexArray->Unbind();

		m_SquareVertexArray.reset(VertexArray::Create()); // create a vertex array object for a square

		float squareVertices[4 * 7] = { -0.75f, -0.75f, 0.0f, 0.0, 1.0, 1.0, 0.0,
										0.75f, -0.75f, 0.0f, 1.0, 0.0, 1.0, 0.0,
										0.75f,  0.75f, 0.0f, 1.0, 1.0, 1.0, 0.0,
									   -0.75f,  0.75f, 0.0f, 1.0, 1.0, 0.0, 0.0 };

		std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
		m_SquareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		{
			// creating the layout in a scope so that it is destroyed after we set it in the vertex buffer
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Colour"}
			};
			m_SquareVertexBuffer->SetLayout(layout);
		}
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 }; // the indices of the vertices that make up the square. As mentioned above we draw the square by drawing 6 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(IndexBuffer::Create(squareIndices, 6));
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		m_SquareVertexArray->Unbind();

		// Read our shaders into the appropriate buffers
		std::string vertexSource = R"(
			#version 450 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
				v_Colour = a_Colour;
			}
		)";// Get source code for vertex shader.
		std::string fragmentSource = R"(
			#version 450 core
			layout(location = 0) out vec4 color;

			in vec4 v_Colour;

			void main()
			{
				color = v_Colour;
			}
		)";// Get source code for fragment shader.

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource)); // create a shader object from the vertex and fragment shader source code.
		
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
		FR_BEGIN_PROFILE_SESSION("Runtime", "../Logs/FractureProfile-Runtime.json");
		while (m_Running)
		{
			static uint32_t frameCount = 0;
			auto m_StartTimepoint = std::chrono::high_resolution_clock::now();
			std::string profile_name = "Fracture::Application::Run() Frame " + std::to_string(frameCount);
			// TODO : The scops are not working correctly.
			FR_PROFILE_SCOPE(profile_name.c_str());

			{ // Rendering
				FR_PROFILE_SCOPE("Rendering Colour");
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // debug clear color
				glClear(GL_COLOR_BUFFER_BIT);


				if (!Input::IsKeyPressed(FR_KEY_TAB))
				{
					m_Shader->Bind();
					m_TriangleVertexArray->Bind();
					glDrawElements(GL_TRIANGLES, m_TriangleVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); // draw the triangle
					// GL_TRIANGLES specifies the mode we want to draw in. Other modes include GL_POINTS and GL_LINES.
					// 3 specifies the number of indices we want to draw.
					// GL_UNSIGNED_INT specifies the type of the indices.
					// nullptr is the offset of where the index data begins in the buffer. Since the index data is at the start of the data array this value is 0.

					// we dont need to provide a pointer because we are using the indexbuffer that we bound earlier attached to m_vertexArray. This means that OpenGL already knows where the index buffer is.
					// This is because we bound the index buffer to the vertex array object. This also means that we don't need to bind the index buffer every time we want to draw something. As long as we have the vertex array object bound we can just call glDrawElements and OpenGL will know which index buffer to use.
				}
				else 
				{
					m_Shader->Bind();
					m_SquareVertexArray->Bind();
					glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); // draw the square
				}
			}

			{ // Layer updates
				FR_PROFILE_SCOPE("LayerStack::OnUpdate");
				// Call the OnUpdate function of all the layers
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}
			}

			{ // ImGui rendering
				FR_PROFILE_SCOPE("ImGuiLayer::Rendering");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			{ // Window updates
				FR_PROFILE_SCOPE("Window::OnUpdate");
				// Call the OnUpdate function of the window
				m_Window->OnUpdate();
			}

			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			FR_CORE_INFO("Frame: {0} Frame time: {1}", frameCount, end - start);

			frameCount++;
		}
		FR_END_PROFILE_SESSION();
	}


}