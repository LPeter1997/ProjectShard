#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
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
#include "src\Gfx\Layer2D.h"
#include "src\Components\DrawSpriteComponent.h"

using namespace Shard;
using namespace Gfx;
using namespace Maths;
using namespace Input;
using namespace Resources;
using namespace Components;


Actor* MakeSprite(float x, float y, Texture2D& tex)
{
	Actor* a = new Actor(Vector3f(x, y, 0));
	DrawSpriteComponent* ds = a->AddComponent<DrawSpriteComponent>();
	ds->Texture = &tex;
	return a;
}

int main(void)
{
	Core::Initialize();

	Window display("Shard Engine", 960, 540);

	ContentManager content("res");

	Text* file1 = content.Load<Text>("basic.vert");
	Text* file2 = content.Load<Text>("basic.frag");

	Texture2D& player = content.Load<Texture2D>("sprite1.png");
	Texture2D& ground = content.Load<Texture2D>("sprite2.png");
	Texture2D& cloud = content.Load<Texture2D>("sprite3.png");
	Texture2D& grass = content.Load<Texture2D>("sprite4.png");

	Font* fnt = content.Load<Font>("font1.ttf");
	FontAtlas atlas = fnt->RenderAtlas(72);

	GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
	Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);
	
	Layer2D layer(new SpriteBatch(10000), shader, ortho);

	layer.Add(MakeSprite(90, 10, cloud));
	layer.Add(MakeSprite(800, 70, cloud));

	layer.Add(MakeSprite(0, 384, ground));
	layer.Add(MakeSprite(128, 384, ground));
	layer.Add(MakeSprite(256, 384, ground));
	layer.Add(MakeSprite(384, 384, ground));
	layer.Add(MakeSprite(384, 512, ground));
	layer.Add(MakeSprite(512, 512, ground));
	layer.Add(MakeSprite(640, 512, ground));
	layer.Add(MakeSprite(768, 512, ground));
	layer.Add(MakeSprite(896, 512, ground));

	layer.Add(MakeSprite(0, 256, grass));
	layer.Add(MakeSprite(384, 256, grass));
	layer.Add(MakeSprite(512, 384, grass));
	layer.Add(MakeSprite(640, 384, grass));
	layer.Add(MakeSprite(768, 384, grass));
	layer.Add(MakeSprite(896, 384, grass));

	layer.Add(MakeSprite(192, 256, player));

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	uint frames = 0;
	clock_t start = std::clock();

	while (!display.IsCloseRequested())
	{
		display.Clear();

		layer.Render();

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