#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>


namespace Sandbox {
	Sandbox2D::Sandbox2D() :
		Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
	{
	}

	void Sandbox2D::OnAttach()
	{
		FR_PROFILE_SCOPE("Application::Sandbox2D::OnAttach");

		m_BigSquare = Fracture::CreateRef<Sandbox::Object>("Texture Square");
		m_Square = Fracture::CreateRef<Sandbox::Object>("Ground Shape");
		m_Logo = Fracture::CreateRef<Sandbox::Object>("Logo Square");

		m_Square->VertexArray = Fracture::VertexArray::Create(); // create a vertex array object for a square

		float squareVertices[4 * 5] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
										0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
										0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
									   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f };

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

		m_Square->Shader = Fracture::ShaderLibrary::Load("square_shader", "assets/shaders/FlatColourShader.glsl");
		m_BigSquare->Shader = Fracture::ShaderLibrary::Load("big_square", "assets/shaders/TextureShader.glsl");
		m_Logo->Shader = Fracture::ShaderLibrary::Load("logo", "assets/shaders/TextureShader.glsl");

		m_Texture = Fracture::Texture2D::Create("assets/textures/base-map.png"); // does not return a raw pointer.
		m_TextureLogo = Fracture::Texture2D::Create("assets/textures/FractureLogo.png"); // does not return a raw pointer.
		m_Texture->Bind(0);
		m_TextureLogo->Bind(1);

		m_BigSquare->Shader->Bind();
		m_BigSquare->Shader->SetInt("u_Texture", 0);
		m_Logo->Shader->Bind();
		m_Logo->Shader->SetInt("u_Texture", 1);

	}

	void Sandbox2D::OnDetach()
	{
	}

	void Sandbox2D::OnUpdate(Fracture::Timestep delta_time)
	{
		FR_PROFILE_SCOPE("Application::Sandbox2D::OnUpdate");
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

		
		m_Square->Shader->Bind();
		m_Square->Shader->SetFloat4("u_Colour", m_SquareColor);

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

	void Sandbox2D::OnImGuiRender()
	{
		FR_PROFILE_SCOPE("Application::Sandbox2D::ImGuiLayer::OnImGuiRender");
		ImGui::Begin("Performance Overview");
		ImGui::Text("Performance");
		ImGui::Text("Frame Rate: %f", 1.0f / m_LastFrameTime);
		ImGui::End();

		ImGui::Begin("Scene Controls");
		ImGui::Text("Small Squares Controls");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat("Square Animation Speed", &m_SqaureAnimationSpeed, 0.0f, 10.0f);
		ImGui::Checkbox("Animate Squares", &m_AnimateSquares);
		ImGui::Text("Control logo position");
		ImGui::SliderFloat3("Logo Position", glm::value_ptr(m_LogoPosition), -1.0f, 1.0f);
		ImGui::End();
	}

	void Sandbox2D::OnEvent(Fracture::Event& e)
	{
		FR_PROFILE_SCOPE("Application::Sandbox2D::OnEvent");
		m_CameraController.OnEvent(e);
	}
}