#include <iostream>
#include <cstdlib>
#include <ctime>
#include "src\Shard.h"
#include "src\Gfx\Window.h"
#include "src\Input\Input.h"
#include "src\Resources\ContentManager.h"
#include "src\Gfx\Shader\ShaderFactory.h"
#include "src\Maths\Matrix.h"
#include "src\Gfx\Buffers\VertexArray.h"
#include "src\Gfx\Buffers\IndexBuffer.h"
#include "src\Gfx\Renderers\SpriteBatch.h"

#define RANDF() ((float)(static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX)))
#define RAND_COL_COMP() ((uint)(RANDF() * 255.0f))
#define RAND_COL() (((RAND_COL_COMP() << 24) * 1) | ((RAND_COL_COMP() << 16) * 1) | ((RAND_COL_COMP() << 8) * 1) | 255)

struct POD
{
	Shard::Maths::Vector3f Position;
	Shard::Maths::Vector2f Size;
	Shard::uint color;
};

int main(void)
{
	using namespace Shard;
	using namespace Gfx;
	using namespace Maths;
	using namespace Input;
	using namespace Resources;

	Core::Initialize();

	Window display("Shard Engine", 960, 540);

	ContentManager content("res");
	Text* file1 = content.Load<Text>("basic.vert");
	Text* file2 = content.Load<Text>("basic.frag");
	GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());

	Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

	shader.Enable();
	shader.SetUniformMat4f("pr_matrix", ortho);
	shader.SetUniformMat4f("ml_matrix", Matrix4f::Translation(Vector3f(0, 0, 0)));

	SpriteBatch batch(shader, 57600);

	POD* sprites = new POD[57600];

	std::srand(std::time(0));
	for (uint i = 0; i < 320; i++)
		for (uint j = 0; j < 180; j++)
			sprites[i * 180 + j] = (POD{ Maths::Vector3f(i * 3, j * 3, 0), Maths::Vector2f(3, 3), RAND_COL() });

	uint frames = 0;
	clock_t start = std::clock();

	while (!display.IsCloseRequested())
	{
		clock_t current_last = std::clock();

		display.Clear();
		
		batch.Begin();

		for (uint i = 0; i < 57600; i++)
		{
			POD& s = sprites[i];
			batch.Draw(s.Position, s.Size, s.color);
		}

		batch.End();
		batch.Render();

		display.Update();
		InputDevices::Update();

		frames++;

		clock_t current = std::clock();

		//std::cout << "Elapsed: " << current - current_last << std::endl;

		if (current - start >= CLOCKS_PER_SEC)
		{
			start += CLOCKS_PER_SEC;
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
		}
	}

	display.Dispose();

	content.UnloadAll();
	Core::Deinitialize();
	return 0;
}