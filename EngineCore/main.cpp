#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"
#include "src\Maths\Matrix.h"
#include "src\Gfx\Buffers\VertexArray.h"
#include "src\Gfx\Buffers\IndexBuffer.h"

using namespace Shard;

int main(void)
{
	Core::Initialize();

	Gfx::Window display("Shard Engine", 960, 540);

	Resources::ContentManager content("res");
	Resources::Text* file1 = content.Load<Resources::Text>("basic.vert");
	Resources::Text* file2 = content.Load<Resources::Text>("basic.frag");
	Gfx::GLSLProgram& shader = Gfx::ShaderFactory::CreateShader(file1->GetText(), file2->GetText());

#if 0
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
#endif

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLuint indicies[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	Gfx::BufferLayout layout;
	layout.Push<Maths::Vector3f>("position");
	Gfx::VertexBuffer* vbo = new Gfx::VertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, layout);
	vbo->Bind();
	vbo->SetData(sizeof(GLfloat) * 12, vertices);

	Gfx::VertexArray vao;
	vao.Bind();
	vao.PushBuffer(vbo);

	Gfx::IndexBuffer ibo(6, indicies);
	vao.Unbind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Maths::Matrix4f ortho = Maths::Matrix4f::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	shader.Enable();
	shader.SetUniformMat4f("pr_matrix", ortho);
	shader.SetUniformMat4f("ml_matrix", Maths::Matrix4f::Translation(Maths::Vector3f(4, 3, 0)));

	while (!display.IsCloseRequested())
	{
		shader.SetUniform2f("light_pos", Maths::Vector2f(Input::Mouse::GetX() * (16.0f / 960.0f), 9.0f - Input::Mouse::GetY() * (9.0f / 540.0f)));
		display.Clear();
		
		vao.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetSize(), GL_UNSIGNED_INT, 0);
		ibo.Unbind();
		vao.Unbind();

		display.Update();
		Input::Update();
	}

	display.Dispose();

	content.UnloadAll();
	Core::Deinitialize();
	return 0;
}