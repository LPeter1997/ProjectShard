#include <iostream>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"
#include "src\Maths\Matrix.h"
#include "src\Gfx\Buffers\VertexArray.h"
#include "src\Gfx\Buffers\IndexBuffer.h"
#include <FreeImage.h>

int main(void)
{
	using namespace Shard;
	using namespace Gfx;
	using namespace Maths;
	using namespace Input;
	using namespace Resources;

	FreeImage_Initialise();
	FreeImage_DeInitialise();

	Core::Initialize();

	Window display("Shard Engine", 960, 540);

	ContentManager content("res");
	Text* file1 = content.Load<Text>("basic.vert");
	Text* file2 = content.Load<Text>("basic.frag");
	GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());

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

	BufferLayout layout;
	layout.Push<Vector3f>("position");
	VertexBuffer* vbo = new VertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, layout);
	vbo->Bind();
	vbo->SetData(sizeof(GLfloat) * 12, vertices);

	VertexArray vao;
	vao.Bind();
	vao.PushBuffer(vbo);

	IndexBuffer ibo(6, indicies);
	vao.Unbind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4f ortho = Matrix4f::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	shader.Enable();
	shader.SetUniformMat4f("pr_matrix", ortho);
	shader.SetUniformMat4f("ml_matrix", Matrix4f::Translation(Vector3f(4, 3, 0)));

	while (!display.IsCloseRequested())
	{
		shader.SetUniform2f("light_pos", Vector2f(Mouse::GetX() * (16.0f / 960.0f), 9.0f - Mouse::GetY() * (9.0f / 540.0f)));
		display.Clear();
		
		vao.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetSize(), GL_UNSIGNED_INT, 0);
		ibo.Unbind();
		vao.Unbind();

		display.Update();
		InputDevices::Update();
	}

	display.Dispose();

	content.UnloadAll();
	Core::Deinitialize();
	return 0;
}