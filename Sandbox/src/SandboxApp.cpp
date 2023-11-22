#include "Fracture.h"
#include "Fracture/EntryPoint.h"

#include "Sandbox2D.h"
#include "Shapes.h"

#include <memory>
#include <glm/gtc/type_ptr.hpp>

class SandboxApp : public Fracture::Application
{
public:
	SandboxApp()
	{
		PushLayer(new Sandbox::Sandbox2D());
	}

	~SandboxApp()
	{

	}
};


Fracture::Application* Fracture::CreateApplication()
{
	return new SandboxApp();
}