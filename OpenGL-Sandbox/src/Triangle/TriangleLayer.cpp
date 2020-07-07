#include "TriangleLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

static void checkCompilation(GLuint shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(shader);

		LOG_ERROR("{0}", infoLog.data());
		// HZ_CORE_ASSERT(false, "Shader compilation failure!");
	}
}

static void checkLinkage(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		LOG_ERROR("{0}", infoLog.data());
		GLCORE_ASSERT(false, "Shader link failure!");
	}
}

static GLuint compileShaders()
{
	GLuint vShader;
	GLuint fShader;
	GLuint cShader;
	GLuint gShader;
	GLuint eShader;
	GLuint program;

	std::string vSourceStr = GLCore::Utils::ReadFileAsString("assets/shaders/Triangle.vert.glsl");
	std::string fSourceStr = GLCore::Utils::ReadFileAsString("assets/shaders/Triangle.frag.glsl");
	std::string cSourceStr = GLCore::Utils::ReadFileAsString("assets/shaders/Triangle.tesc.glsl");
	std::string gSourceStr = GLCore::Utils::ReadFileAsString("assets/shaders/Triangle.geom.glsl");
	std::string eSourceStr = GLCore::Utils::ReadFileAsString("assets/shaders/Triangle.tese.glsl");

	vShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vSource = vSourceStr.c_str();
	glShaderSource(vShader, 1, &vSource, 0);
	glCompileShader(vShader);
	checkCompilation(vShader);

	cShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	const GLchar* cSource = cSourceStr.c_str();
	glShaderSource(cShader, 1, &cSource, 0);
	glCompileShader(cShader);
	checkCompilation(cShader);

	eShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	const GLchar* eSource = eSourceStr.c_str();
	glShaderSource(eShader, 1, &eSource, 0);
	glCompileShader(eShader);
	checkCompilation(eShader);

	gShader = glCreateShader(GL_GEOMETRY_SHADER);
	const GLchar* gSource = gSourceStr.c_str();
	glShaderSource(gShader, 1, &gSource, 0);
	glCompileShader(gShader);
	checkCompilation(gShader);

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fSource = fSourceStr.c_str();
	glShaderSource(fShader, 1, &fSource, 0);
	glCompileShader(fShader);
	checkCompilation(fShader);

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, cShader);
	glAttachShader(program, eShader);
	glAttachShader(program, gShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	checkLinkage(program);


	glDetachShader(program, vShader);
	glDetachShader(program, cShader);
	glDetachShader(program, eShader);
	glDetachShader(program, gShader);
	glDetachShader(program, fShader);
	glDeleteShader(vShader);
	glDeleteShader(cShader);
	glDeleteShader(eShader);
	glDeleteShader(gShader);
	glDeleteShader(fShader);

	return program;
}

TriangleLayer::TriangleLayer()
{
}

TriangleLayer::~TriangleLayer()
{
}

void TriangleLayer::OnAttach()
{
	EnableGLDebugging();
	// Init here

	m_Program = compileShaders();
	//m_Program = Shader::FromGLSLTextFiles("assets/shaders/Triangle.vert.glsl", "assets/shaders/Triangle.frag.glsl")->GetRendererID();
	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TriangleLayer::OnDetach()
{
	// Shutdown here
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteProgram(m_Program);
}

void TriangleLayer::OnEvent(Event& event)
{
	// Events here
}

void TriangleLayer::OnUpdate(Timestep ts)
{
	// Render here

	static float currTime = 0;
	currTime += ts;

	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_Program);

	GLfloat offset[] = {
		(float)sin(currTime) * 0.5f,
		(float)cos(currTime) * 0.6f,
		0.0f, 0.0f
	};

	GLfloat fColor[] = { sin(currTime)*0.8f, cos(currTime)*0.2f, 0.8f, 1.0f };

	glVertexAttrib4fv(0, offset);
	glVertexAttrib4fv(1, fColor);

	glPointSize(5.0f);
	glDrawArrays(GL_PATCHES, 0, 3);
}

void TriangleLayer::OnImGuiRender()
{
	// ImGui here
}
