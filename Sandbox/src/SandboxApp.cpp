#include "Fracture.h"

#include "Shapes.h"

#include <memory>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Fracture::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(16.0f/9.0f, false), m_BigSquare(std::make_shared<Sandbox::Object>("Texture Square")), m_Square(std::make_shared<Sandbox::Object>("Ground Square")), m_Logo(std::make_shared<Sandbox::Object>("Logo Square"))
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

		m_Square->Shader = Fracture::ShaderLibrary::Load("square_shader", "assets/shaders/TextureShader.glsl");
		m_BigSquare->Shader = Fracture::ShaderLibrary::Load("big_square", "assets/shaders/TextureShader.glsl");
		m_Logo->Shader = Fracture::ShaderLibrary::Load("logo", "assets/shaders/TextureShader.glsl");

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
		{
			FR_PROFILE_SCOPE("CameraController::OnUpdate");
			m_CameraController.OnUpdate(delta_time);
		}

		Fracture::Renderer::BeginScene(m_CameraController.GetCamera());
		Fracture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.2f, 1.0f });
		Fracture::RenderCommand::Clear();

		if (m_AnimateSquares)
			m_Square->Transform.Rotate(glm::vec3(0.0f, 0.0f, m_SqaureAnimationSpeed * delta_time));
		
		glm::vec4 redColour(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColour(0.2f, 0.3f, 0.8f, 1.0f);

		for (int x = -10; x < 10; x++)
		{
			for (int y = -10; y < 10; y++)
			{
				FR_PROFILE_SCOPE("Renderer::Submit");
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

	void OnEvent(Fracture::Event& e) override
	{
		FR_PROFILE_SCOPE("Application::ExampleLayer::OnEvent");
		m_CameraController.OnEvent(e);
	}

	void OnImGuiRender() override
	{
		FR_PROFILE_SCOPE("Application::ImGuiLayer::OnImGuiRender");
		ImGui::Begin("Performance Overview");
		ImGui::Text("Performance");
		ImGui::Text("Frame Rate: %f", 1.0f/m_LastFrameTime);
		ImGui::End();

		ImGui::Begin("Scene Controls");
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

	Fracture::OrthographicCameraController m_CameraController;
	bool m_AnimateSquares = false;

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