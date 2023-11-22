#pragma once
#include "Fracture.h"
#include "Shapes.h"


namespace Sandbox
{
	class Sandbox2D : public Fracture::Layer
	{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Fracture::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Fracture::Event& e) override;
	private:
		Fracture::Ref<Sandbox::Object> m_BigSquare;
		Fracture::Ref<Sandbox::Object> m_Logo;
		Fracture::Ref<Sandbox::Object> m_Square;

		Fracture::Ref<Fracture::Texture2D> m_Texture;
		Fracture::Ref<Fracture::Texture2D> m_TextureBlue;
		Fracture::Ref<Fracture::Texture2D> m_TextureLogo;

		Fracture::OrthographicCameraController m_CameraController;

		Fracture::Ref<Fracture::VertexArray> m_SquareVA;
		Fracture::Ref<Fracture::Shader> m_FlatColorShader;

		Fracture::Ref<Fracture::Texture2D> m_CheckerboardTexture;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		bool m_AnimateSquares = false;

		glm::vec3 m_LogoPosition = { -1.0f, 0.0f, 0.0f };

		Fracture::Timestep m_LastFrameTime;

		float m_SqaureAnimationSpeed = 0.5f;
	};
}