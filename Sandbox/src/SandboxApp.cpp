#include "Fracture.h"

#include "Shapes.h"

#include <memory>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Fracture::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f, -100.0f, 100.0f), m_BigSquare(std::make_shared<Sandbox::Object>("Texture Square")), m_Square(std::make_shared<Sandbox::Object>("Ground Square")), m_Logo(std::make_shared<Sandbox::Object>("Logo Square"))
	{
		m_Square->VertexArray = Fracture::VertexArray::Create(); // create a vertex array object for a square

		float squareVertices[4 * 5] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
										0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
										0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
									   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f};

		Fracture::Ref<Fracture::VertexBuffer> m_SquareVertexBuffer = Fracture::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		{
			// creating the layout in a scope so that it is destroyed after we set it in the vertex buffer
			Fracture::BufferLayout layout = {
				{ Fracture::ShaderDataType::Float3, "a_Position" },
				{ Fracture::ShaderDataType::Float2, "a_TexCoord"}
			};
			m_SquareVertexBuffer->SetLayout(layout);
		}
		m_Square->VertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 }; // the indices of the vertices that make up the square. As mentioned above we draw the square by drawing 6 vertices in counter-clockwise order. The indices are used to specify the order in which the vertices should be drawn.

		m_Square->VertexArray->SetIndexBuffer(Fracture::IndexBuffer::Create(squareIndices, 6));

		m_Square->Transform.SetScale(glm::vec3(0.1f));

		m_BigSquare->VertexArray = Fracture::VertexArray::Create(); // create a vertex array object for a square

		m_BigSquare->VertexArray->AddVertexBuffer(m_SquareVertexBuffer);
		m_BigSquare->VertexArray->SetIndexBuffer(Fracture::IndexBuffer::Create(squareIndices, 6));
		m_BigSquare->Transform.SetScale(glm::vec3(1.5f));

		m_Logo->VertexArray = Fracture::VertexArray::Create(); // create a vertex array object for a square

		m_Logo->VertexArray->AddVertexBuffer(m_SquareVertexBuffer);
		m_Logo->VertexArray->SetIndexBuffer(Fracture::IndexBuffer::Create(squareIndices, 6));
		m_Logo->Transform.SetScale(glm::vec3(0.5f));

		//// Read our shaders into the appropriate buffers
		//std::string flatColourvertexSource = R"(
		//	#version 450 core
		//	layout(location = 0) in vec3 a_Position;
		//	
		//	uniform mat4 u_ViewProjection;
		//	uniform mat4 u_Transform;

		//	void main()
		//	{
		//		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		//	}
		//)";// Get source code for vertex shader.
		//std::string flatColourfragmentSource = R"(
		//	#version 450 core
		//	layout(location = 0) out vec4 color;

		//	uniform vec4 u_Color;

		//	void main()
		//	{
		//		color = u_Color;
		//	}
		//)";// Get source code for fragment shader.

		std::string textureVertexSource = R"(
			#version 450 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TexCoord;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_TexCoord = a_TexCoord;
			}
		)";// Get source code for vertex shader.
		std::string texturefragmentSource = R"(
			#version 450 core
			layout(location = 0) out vec4 color;

			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";// Get source code for fragment shader.

		m_Square->Shader = Fracture::Shader::Create(textureVertexSource, texturefragmentSource);
		m_BigSquare->Shader = Fracture::Shader::Create(textureVertexSource, texturefragmentSource);
		m_Logo->Shader = Fracture::Shader::Create(textureVertexSource, texturefragmentSource);

		m_Texture = Fracture::Texture2D::Create("assets/textures/base-map.png"); // does not return a raw pointer.
		m_TextureBlue = Fracture::Texture2D::Create(256, 256, glm::vec4(0.2f, 0.3f, 0.8f, 1.0f)); // does not return a raw pointer.
		m_TextureLogo = Fracture::Texture2D::Create("assets/textures/FractureLogo.png"); // does not return a raw pointer.
		m_Texture->Bind(0);
		m_TextureBlue->Bind(1);
		m_TextureLogo->Bind(2);

		m_BigSquare->Shader->Bind();
		m_BigSquare->Shader->SetInt("u_Texture", 0);
		m_Square->Shader->Bind();
		m_Square->Shader->SetInt("u_Texture", 1);
		m_Logo->Shader->Bind();
		m_Logo->Shader->SetInt("u_Texture", 2);

		//m_Camera.GetCameraTransform().SetRotation(glm::vec3(-3.1415f / 3.0f, 0.0f, -3.1415f / 4.0f));

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

		if (m_isIsometric)
		{
			m_Camera.GetCameraTransform().SetRotation(glm::vec3(-3.1415f / 3.0f, 0.0f, -3.1415f / 4.0f));
		}
		else
		{
			m_Camera.GetCameraTransform().SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		}

		Fracture::Renderer::BeginScene(m_Camera);
		Fracture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.2f, 1.0f });
		Fracture::RenderCommand::Clear();

		if (m_AnimateSquares)
			m_Square->Transform.Rotate(glm::vec3(0.0f, 0.0f, m_SqaureAnimationSpeed * delta_time));
		
		glm::vec4 redColour(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColour(0.2f, 0.3f, 0.8f, 1.0f);

		for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++)
			{
				Fracture::TransformComponent local_transform = m_Square->Transform;
				local_transform.Translate(glm::vec3(x * 0.1f, y * 0.1f, 0.0f));
				Fracture::Renderer::Submit(m_Square->VertexArray, m_Square->Shader, local_transform.GetTransform());
			}
		}

		Fracture::Renderer::Submit(m_BigSquare->VertexArray, m_BigSquare->Shader, m_BigSquare->Transform.GetTransform());

		m_Logo->Transform.SetPosition(m_LogoPosition);
		Fracture::Renderer::Submit(m_Logo->VertexArray, m_Logo->Shader, m_Logo->Transform.GetTransform());

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

		ImGui::Begin("Scene Controls");
		ImGui::Text("Camera Controls");
		ImGui::Text("Arrow keys to move");
		ImGui::SliderFloat("Camera Translation Speed", &m_cameraTranslationSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat("Camera Rotation Speed", &m_cameraRotationSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat("Camera Zoom Speed", &m_cameraZoomSpeed, 0.0f, 10.0f);
		ImGui::Checkbox("Set to isometric view", &m_isIsometric);
		ImGui::Text("Small Squares Controls");
		ImGui::Text("A to toggle animation");
		ImGui::SliderFloat("Square Animation Speed", &m_SqaureAnimationSpeed, 0.0f, 10.0f);
		ImGui::Checkbox("Animate Squares", &m_AnimateSquares);
		ImGui::Text("Control logo position");
		ImGui::SliderFloat3("Logo Position", glm::value_ptr(m_LogoPosition), -1.0f, 1.0f);
		ImGui::End();
	}
private:
	Fracture::Ref<Sandbox::Object> m_BigSquare;
	Fracture::Ref<Sandbox::Object> m_Logo;
	Fracture::Ref<Sandbox::Object> m_Square;

	Fracture::Ref<Fracture::Texture2D> m_Texture;
	Fracture::Ref<Fracture::Texture2D> m_TextureBlue;
	Fracture::Ref<Fracture::Texture2D> m_TextureLogo;

	Fracture::OrthographicCamera m_Camera;
	float m_cameraTranslationSpeed = 1.0f;
	float m_cameraRotationSpeed = 1.0f;
	float m_cameraZoomSpeed = 2.0f;
	bool m_AnimateSquares = false;
	bool m_isIsometric = false;

	glm::vec3 m_LogoPosition = { -1.0f, 0.0f, 0.0f };

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