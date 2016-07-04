
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
#include "src\Components\Component.h"
#include "src\Logic\GameStateManager.h"
#include "src\Logic\GameState.h"
#include "src\GUI\GUILayer.h"
#include "src\GUI\GUILabel.h"
#include "src\GUI\GUIButton.h"

using namespace Shard;
using namespace Gfx;
using namespace Maths;
using namespace Input;
using namespace Resources;
using namespace Components;
using namespace Logic;
using namespace GUI;

class DrawSpriteComponent : public Component
{
protected:
	Transform& m_Position;

public:
	Gfx::Texture2D* Texture;

public:
	DrawSpriteComponent(Actor& a)
		: Component(a), m_Position(m_Actor.GetTransform()), Texture(nullptr)
	{
	}

	inline void Render(Gfx::Renderer2D& renderer) override
	{
		renderer.DrawTexture(m_Position.Position, *Texture);
	}
};

class PlayerInputComponent : public Component
{
protected:
	Transform& m_Position;

public:
	PlayerInputComponent(Actor& a)
		: Component(a), m_Position(m_Actor.GetTransform())
	{
	}

	inline void Update(float delta) override
	{
		float dx = 0;
		float dy = 0;

		if (Keyboard::IsKeyDown(Keys::Up)) dy -= 100;
		if (Keyboard::IsKeyDown(Keys::Down)) dy += 100;
		if (Keyboard::IsKeyDown(Keys::Left)) dx -= 100;
		if (Keyboard::IsKeyDown(Keys::Right)) dx += 100;

		m_Position.Position.x += dx * delta;
		m_Position.Position.y += dy * delta;
	}
};

Actor* MakeSprite(float x, float y, Texture2D& tex)
{
	Actor* a = new Actor(Vector3f(x, y, 0));
	DrawSpriteComponent* ds = a->AddComponent<DrawSpriteComponent>();
	ds->Texture = &tex;
	return a;
}

class TestState : public GameState
{
private:
	ContentManager* content;
	Layer2D* layer;
	Texture2D* player;
	Texture2D* cloud;
	Texture2D* grass;
	Texture2D* ground;
	FontAtlas* atlas;
	GUILayer* gui;
	GUILabel* fpsCounter;

public:
	TestState() {}

protected:
	void Initialize() override
	{
		content = new ContentManager("res");
		
		Text* file1 = content->Load<Text>("basic.vert");
		Text* file2 = content->Load<Text>("basic.frag");

		player = content->Load<Texture2D>("sprite1.png");
		ground = content->Load<Texture2D>("sprite2.png");
		cloud = content->Load<Texture2D>("sprite3.png");
		grass = content->Load<Texture2D>("sprite4.png");

		Font* fnt = content->Load<Font>("font1.ttf");
		atlas = fnt->RenderAtlas(72);

		GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

		layer = new Layer2D(new SpriteBatch(10000), shader, ortho);

		layer->Add(MakeSprite(90, 10, *cloud));
		layer->Add(MakeSprite(800, 70, *cloud));

		layer->Add(MakeSprite(0, 384, *ground));
		layer->Add(MakeSprite(128, 384, *ground));
		layer->Add(MakeSprite(256, 384, *ground));
		layer->Add(MakeSprite(384, 384, *ground));
		layer->Add(MakeSprite(384, 512, *ground));
		layer->Add(MakeSprite(512, 512, *ground));
		layer->Add(MakeSprite(640, 512, *ground));
		layer->Add(MakeSprite(768, 512, *ground));
		layer->Add(MakeSprite(896, 512, *ground));

		layer->Add(MakeSprite(0, 256, *grass));
		layer->Add(MakeSprite(384, 256, *grass));
		layer->Add(MakeSprite(512, 384, *grass));
		layer->Add(MakeSprite(640, 384, *grass));
		layer->Add(MakeSprite(768, 384, *grass));
		layer->Add(MakeSprite(896, 384, *grass));

		Actor* pa = MakeSprite(192, 256, *player);
		pa->AddComponent<PlayerInputComponent>();
		layer->Add(pa);

		GLSLProgram& shader2 = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		gui = new GUILayer(new SpriteBatch(10000), shader2, ortho);
		fpsCounter = new GUILabel(Vector2f(10, 10), *atlas, Vector4f(0, 0, 1, 1), "FPS:");
		gui->Add(fpsCounter);
		GUILabel* btnl = new GUILabel(Vector2f(0, 0), *atlas, Vector4f(1, 1, 1, 1), "Press Me");
		gui->Add(new GUIButton(Vector2f(500, 20), Vector4f(0.6f, 0, 0, 1), btnl));
	}

	inline void Tick() override
	{
		fpsCounter->SetText("FPS: " + std::to_string(m_FPS));
	}

	inline void Update(float delta) override
	{
		layer->Update(delta);
		gui->Update(delta);
	}

	inline void Render() override
	{
		layer->Render();
		gui->Render();
	}

	void Deinitialize() override
	{
		content->UnloadAll();
		delete player;
		delete grass;
		delete ground;
		delete cloud;
		delete content;
	}
};

int main(void)
{
	Core::Initialize();

	Window display("Shard Engine", 960, 540);

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	GameStateManager::PushState(new TestState());
	GameStateManager::Start();

	display.Dispose();
	Core::Deinitialize();

	return 0;
}