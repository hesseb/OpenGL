#include "GLCore.h"
#include "SandboxLayer.h"
#include "Triangle/TriangleLayer.h"

using namespace GLCore;

class Sandbox : public Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
		//PushLayer(new TriangleLayer());
	}
};

int main()
{
	std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>();
	app->Run();
}