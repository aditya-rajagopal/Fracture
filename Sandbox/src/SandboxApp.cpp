#include "Fracture.h"

#include "Shapes.h"

#include <memory>


class ExampleLayer : public Fracture::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f, -100.0f, 100.0f), m_Triangle(std::make_shared<Sandbox::Object>("Triangle")), m_Square(std::make_shared<Sandbox::Object>("Square"))
	{
		m_Triangle->VertexArray.reset(Fracture::VertexArray::Create());
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
		m_Triangle->VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 }; // the indices of the vertices that make up the triangle. As mentioned above we draw the triangle by drawing 3 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		std::shared_ptr<Fracture::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Fracture::IndexBuffer::Create(indices, 3));
		m_Triangle->VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_Triangle->VertexArray->Unbind();

		m_Square->VertexArray.reset(Fracture::VertexArray::Create()); // create a vertex array object for a square

		float squareVertices[4 * 7] = {-0.5f, -0.5f, 0.0f, 0.2, 0.3, 0.8, 0.0,
										0.5f, -0.5f, 0.0f, 0.2, 0.3, 0.8, 0.0,
										0.5f,  0.5f, 0.0f, 0.2, 0.3, 0.8, 0.0,
									   -0.5f,  0.5f, 0.0f, 0.2, 0.3, 0.8, 0.0 };

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
		m_Square->VertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 }; // the indices of the vertices that make up the square. As mentioned above we draw the square by drawing 6 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		std::shared_ptr<Fracture::IndexBuffer> m_SquareIndexBuffer;
		m_SquareIndexBuffer.reset(Fracture::IndexBuffer::Create(squareIndices, 6));
		m_Square->VertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		m_Square->Transform.SetScale(glm::vec3(0.1f));

		m_Square->VertexArray->Unbind();

		// Read our shaders into the appropriate buffers
		std::string vertexSource = R"(
			#version 450 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Colour;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		std::shared_ptr<Fracture::Shader> local_shader;
		local_shader.reset(Fracture::Shader::Create(vertexSource, fragmentSource));
		m_Square->Shader = local_shader;
		m_Triangle->Shader = local_shader;

		m_Camera.GetCameraTransform().SetRotation(glm::vec3(-3.1415f / 3.0f, 0.0f, -3.1415f / 4.0f));

	}

	void OnUpdate(Fracture::Timestep delta_time) override
	{
		FR_PROFILE_SCOPE("Application::ExampleLayer::OnUpdate");
		//FR_TRACE("Delta time: {0}s ({1}ms)", delta_time.GetSeconds(), delta_time.GetMilliseconds());
		m_LastFrameTime = delta_time;

		if (Fracture::Input::IsKeyPressed(FR_KEY_DOWN))
			m_Camera.Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(-1.0f, -1.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_UP))
			m_Camera.Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(1.0f, 1.0f, 0.0f));

		if (Fracture::Input::IsKeyPressed(FR_KEY_LEFT))
			m_Camera.Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(-1.0f, 1.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_RIGHT))
			m_Camera.Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(1.0f, -1.0f, 0.0f));

		Fracture::Renderer::BeginScene(m_Camera);
		Fracture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.2f, 1.0f });
		Fracture::RenderCommand::Clear();

		m_Square->Transform.Rotate(glm::vec3(0.0f, 0.0f, m_SqaureAnimationSpeed * delta_time));
		
		for (int x = -10; x < 10; x++)
		{
			for (int y = -10; y < 10; y++)
			{
				Fracture::TransformComponent local_transform = m_Square->Transform;
				local_transform.Translate(glm::vec3(x * 0.1f, y * 0.1f, 0.0f));
				//local_transform.Rotate(glm::vec3(0.0f, 0.0f, m_SqaureAnimationSpeed * delta_time));
				Fracture::Renderer::Submit(m_Square->VertexArray, m_Square->Shader, local_transform.GetTransform());
			}
		}


		//Fracture::Renderer::Submit(m_Triangle->VertexArray, m_Triangle->Shader, m_Triangle->Transform.GetTransform());

		Fracture::Renderer::EndScene();
	}

	void OnEvent(Fracture::Event& event) override
	{
		Fracture::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Fracture::MouseScrolledEvent>(FRACTURE_BIND_EVENT_FN(ExampleLayer::OnMouseScrollEvent));
	}

	bool OnMouseScrollEvent(Fracture::MouseScrolledEvent& event)
	{
		m_Camera.Zoom(-event.GetYOffset() * m_cameraZoomSpeed * m_LastFrameTime);

		return false;
	}

	void OnImGuiRender() override
	{
		FR_PROFILE_SCOPE("Application::ImGuiLayer::OnImGuiRender");
		ImGui::Begin("Performance Overview");
		ImGui::Text("Performance");
		ImGui::Text("Frame Rate: %f", 1.0f/m_LastFrameTime);
		ImGui::End();
	}
private:
	std::shared_ptr<Sandbox::Object> m_Triangle;
	std::shared_ptr<Sandbox::Object> m_Square;

	Fracture::OrthographicCamera m_Camera;
	float m_cameraTranslationSpeed = 1.0f;
	float m_cameraRotationSpeed = 1.0f;
	float m_cameraZoomSpeed = 2.0f;

	Fracture::Timestep m_LastFrameTime;

	float m_SqaureAnimationSpeed = 0.5f;
};

class SandboxApp : public Fracture::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};


Fracture::Application* Fracture::CreateApplication()
{
	return new SandboxApp();
}