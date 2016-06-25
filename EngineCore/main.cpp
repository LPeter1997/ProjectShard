#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"
#include "src\Maths\Matrix.h"

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
		4, 3, 0,
		12, 3, 0,
		4, 6, 0,
		4, 6, 0,
		12, 6, 0,
		12, 3, 0
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Maths::Matrix4f ortho = Maths::Matrix4f::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	shader.Enable();
	shader.SetUniformMat4f("pr_matrix", ortho);
	//shader.SetUniformMat4f("ml_matrix", Maths::Matrix4f::Rotation(45, Maths::Vector3f(0, 0, 1)));
	shader.SetUniform2f("light_pos", Maths::Vector2f(4, 1.5f));
	while (!display.IsCloseRequested())
	{
		shader.SetUniform2f("light_pos", Maths::Vector2f(Input::Mouse::GetX() * (16.0f / 960.0f), 9.0f - Input::Mouse::GetY() * (9.0f / 540.0f)));
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