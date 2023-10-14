#include "Fracture.h"


class Sandbox : public Fracture::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


Fracture::Application* Fracture::CreateApplication()
{
	return new Sandbox();
}