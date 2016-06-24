#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"

using namespace Shard;

int main(void)
{
	Core::Initialize();

	Gfx::Window display("Shard Engine", 960, 540);

	Resources::ContentManager content("res");
	Resources::Text* file1 = content.Load<Resources::Text>("basic.vert");
	Resources::Text* file2 = content.Load<Resources::Text>("basic.frag");
	Gfx::GLSLProgram& shader = Gfx::ShaderFactory::CreateShader(file1->GetText(), file2->GetText());

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glClearColor(0.2f, 0.3f, 1.0f, 1.0f);

	shader.Enable();
	while (!display.IsCloseRequested())
	{
		display.Clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		display.Update();
		Input::Update();

		if (Input::Keyboard::IsKeyDown(Input::Keys::A))
		{
			std::cout << "A megnyomva" << std::endl;
		}
	}

	display.Dispose();

	content.UnloadAll();
	Core::Deinitialize();
	return 0;
}