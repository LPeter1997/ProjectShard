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
#include "src\Gfx\ColorUtils.h"

#define RANDF() ((float)(static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX)))
#define RAND_COL_COMP() ((uint)(RANDF() * 255.0f))
#define RAND_COL() ((255 << 24) | ((RAND_COL_COMP() << 16) * 1) | ((RAND_COL_COMP() << 8) * 1) | ((RAND_COL_COMP()) * 1))

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

	Texture2D* player = content.Load<Texture2D>("sprite1.png");
	Texture2D* ground = content.Load<Texture2D>("sprite2.png");
	Texture2D* cloud = content.Load<Texture2D>("sprite3.png");
	Texture2D* grass = content.Load<Texture2D>("sprite4.png");

	Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

	shader.Enable();
	shader.SetUniformMat4f("pr_matrix", ortho);
	shader.SetUniformMat4f("ml_matrix", Matrix4f::Translation(Vector3f(0, 0, 0)));

	SpriteBatch batch(57600);

#ifdef TEST_MANY_SPRITES
	POD* sprites = new POD[57600];

	std::srand(std::time(0));
	for (uint i = 0; i < 320; i++)
		for (uint j = 0; j < 180; j++)
			sprites[i * 180 + j] = (POD{ Maths::Vector3f(i * 3, j * 3, 0), Maths::Vector2f(3, 3), RAND_COL() });
#endif

	uint frames = 0;
	clock_t start = std::clock();

	shader.Enable();

	int texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31
	};

	shader.SetUniform1iv("textures", texIDs, 32);

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	while (!display.IsCloseRequested())
	{
		display.Clear();
		
		batch.Begin();

#ifdef TEST_MANY_SPRITES
		for (uint i = 0; i < 57600; i++)
		{
			POD& s = sprites[i];
			batch.Draw(s.Position, s.Size, s.color);
		}
#endif

		/*
		batch.Draw(Vector3f(90, 10, 0), *cloud);
		batch.Draw(Vector3f(800, 70, 0), *cloud);

		batch.Draw(Vector3f(0, 384, 0), *ground);
		batch.Draw(Vector3f(128, 384, 0), *ground);
		batch.Draw(Vector3f(256, 384, 0), *ground);
		batch.Draw(Vector3f(384, 384, 0), *ground);
		batch.Draw(Vector3f(384, 512, 0), *ground);
		batch.Draw(Vector3f(512, 512, 0), *ground);
		batch.Draw(Vector3f(640, 512, 0), *ground);
		batch.Draw(Vector3f(768, 512, 0), *ground);
		batch.Draw(Vector3f(896, 512, 0), *ground);

		batch.Draw(Vector3f(0, 256, 0), *grass);
		batch.Draw(Vector3f(384, 256, 0), *grass);
		batch.Draw(Vector3f(512, 384, 0), *grass);
		batch.Draw(Vector3f(640, 384, 0), *grass);
		batch.Draw(Vector3f(768, 384, 0), *grass);
		batch.Draw(Vector3f(896, 384, 0), *grass);

		batch.Draw(Vector3f(192, 256, 0), *player);
		*/

		// STACKING ///////////////////////////////////////////////////////////
		batch.GetTransformationStack().Push(Matrix4f::Translation(Vector3f(100, 100, 0)));

		batch.Draw(Vector3f(0, 0, 0), Vector2f(200, 70), ColorUtils::RGBATo32IntABGR(Vector4f(1, 0, 0, 1)));

		batch.GetTransformationStack().Push(Matrix4f::Translation(Vector3f(10, 10, 0)));

		batch.Draw(Vector3f(0, 0, 0), Vector2f(180, 50), ColorUtils::RGBATo32IntABGR(Vector4f(0, 0, 1, 1)));

		batch.GetTransformationStack().Pop();

		batch.Draw(Vector3f(0, 0, 0), Vector2f(20, 20), ColorUtils::RGBATo32IntABGR(Vector4f(0, 1, 0, 1)));

		batch.GetTransformationStack().Pop();
		////////////////////////////////////////////////////////////////////////

		batch.End();
		batch.Render();

		display.Update();
		InputDevices::Update();

		frames++;

		clock_t current = std::clock();

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