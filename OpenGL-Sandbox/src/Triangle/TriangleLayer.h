#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

class TriangleLayer : public GLCore::Layer
{
public:
	TriangleLayer();
	virtual ~TriangleLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:

	GLuint m_Program;
	GLuint m_VAO;
};