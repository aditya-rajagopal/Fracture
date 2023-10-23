#include "Fracture.h"


class ExampleLayer : public Fracture::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		FR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Fracture::Event& event) override
	{
		FR_TRACE("{0}", event);
	}
};

class Sandbox : public Fracture::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Fracture::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};


Fracture::Application* Fracture::CreateApplication()
{
	return new Sandbox();
}