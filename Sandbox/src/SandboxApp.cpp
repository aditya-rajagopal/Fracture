#include "Fracture.h"

#include <memory>


class ExampleLayer : public Fracture::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6, 1.6, -0.9, 0.9)
	{
		m_TriangleVertexArray.reset(Fracture::VertexArray::Create());
		float vertices[3 * 7] = { -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 0.0, // first vertex (left bottom) position, colour
								   0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 0.0, // second vertex (right bottom) position, colour
								   0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0, 0.0 }; // third vertex (top center) position, colour

		std::shared_ptr<Fracture::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Fracture::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			// creating the layout in a scope so that it is destroyed after we set it in the vertex buffer
			Fracture::BufferLayout layout = {
				{ Fracture::ShaderDataType::Float3, "a_Position" },
				{ Fracture::ShaderDataType::Float4, "a_Colour"}
			};
			m_VertexBuffer->SetLayout(layout);
		}
		m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 }; // the indices of the vertices that make up the triangle. As mentioned above we draw the triangle by drawing 3 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		std::shared_ptr<Fracture::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Fracture::IndexBuffer::Create(indices, 3));
		m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);
		m_TriangleVertexArray->Unbind();

		m_SquareVertexArray.reset(Fracture::VertexArray::Create()); // create a vertex array object for a square

		float squareVertices[4 * 7] = { -0.75f, -0.75f, 0.0f, 0.0, 1.0, 1.0, 0.0,
										0.75f, -0.75f, 0.0f, 1.0, 0.0, 1.0, 0.0,
										0.75f,  0.75f, 0.0f, 1.0, 1.0, 1.0, 0.0,
									   -0.75f,  0.75f, 0.0f, 1.0, 1.0, 0.0, 0.0 };

		std::shared_ptr<Fracture::VertexBuffer> m_SquareVertexBuffer;
		m_SquareVertexBuffer.reset(Fracture::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		{
			// creating the layout in a scope so that it is destroyed after we set it in the vertex buffer
			Fracture::BufferLayout layout = {
				{ Fracture::ShaderDataType::Float3, "a_Position" },
				{ Fracture::ShaderDataType::Float4, "a_Colour"}
			};
			m_SquareVertexBuffer->SetLayout(layout);
		}
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 }; // the indices of the vertices that make up the square. As mentioned above we draw the square by drawing 6 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		std::shared_ptr<Fracture::IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(Fracture::IndexBuffer::Create(squareIndices, 6));
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		m_SquareVertexArray->Unbind();

		// Read our shaders into the appropriate buffers
		std::string vertexSource = R"(
			#version 450 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;
			
			uniform mat4 u_ViewProjection;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(Fracture::Shader::Create(vertexSource, fragmentSource)); // create a shader object from the vertex and fragment shader source code.

	}

	void OnUpdate() override
	{
		FR_PROFILE_SCOPE("Application::ExampleLayer::OnUpdate");

		if (Fracture::Input::IsKeyPressed(FR_KEY_LEFT))
			m_Camera.Translate(cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_RIGHT))
			m_Camera.Translate(cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_UP))
			m_Camera.Translate(cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_DOWN))
			m_Camera.Translate(cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f));

		if (Fracture::Input::IsKeyPressed(FR_KEY_A))
			m_Camera.Rotate(cameraSpeed * 10.0f);
		else if (Fracture::Input::IsKeyPressed(FR_KEY_D))
			m_Camera.Rotate(-cameraSpeed * 10.0f);

		Fracture::Renderer::BeginScene(m_Camera);
		Fracture::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Fracture::RenderCommand::Clear();


		if (!Fracture::Input::IsKeyPressed(FR_KEY_TAB))
		{
			Fracture::Renderer::Submit(m_TriangleVertexArray, m_Shader);
		}
		else
		{
			Fracture::Renderer::Submit(m_SquareVertexArray, m_Shader);
		}

		Fracture::Renderer::EndScene();
	}

	void OnEvent(Fracture::Event& event) override
	{
		//FR_TRACE("{0}", event);
	}

	void OnImGuiRender() override
	{
		FR_PROFILE_SCOPE("Application::ImGuiLayer::OnImGuiRender");
		ImGui::Begin("Test Window");
		ImGui::Text("Hello World");
		ImGui::End();
	}
private:
	std::shared_ptr<Fracture::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<Fracture::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Fracture::Shader> m_Shader;
	Fracture::OrthographicCamera m_Camera;
	float cameraSpeed = 0.005f;
};

class Sandbox : public Fracture::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};


Fracture::Application* Fracture::CreateApplication()
{
	return new Sandbox();
}