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
		/*auto[x, y] = Fracture::Input::GetMousePosition();
		FR_TRACE("Mouse Pos {0}, {1}", x, y);*/

		if (Fracture::Input::IsKeyPressed(FR_KEY_TAB))
			FR_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Fracture::Event& event) override
	{
		//FR_TRACE("{0}", event);
	}
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