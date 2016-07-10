
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
#include "src\Sfx\AudioListener.h"
#include "src\Sfx\SoundEffect.h"
#include "src\Sfx\SoundEffect3D.h"

using namespace Shard;
using namespace Gfx;
using namespace Maths;
using namespace Input;
using namespace Resources;
using namespace Components;
using namespace Logic;
using namespace GUI;
using namespace Sfx;

class TestState : public GameState
{
private:
	ContentManager* content;
	Layer2D* layer;
	FontAtlas* atlas;
	GUILayer* gui;
	Sound* song;
	SoundEffect* sf;

public:
	TestState() {}

protected:
	void Initialize() override
	{
		content = new ContentManager("res");
		
		Text* file1 = content->Load<Text>("basic.vert");
		Text* file2 = content->Load<Text>("basic.frag");

		Font* fnt = content->Load<Font>("font1.ttf");
		atlas = fnt->RenderAtlas(72);

		GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

		layer = new Layer2D(new SpriteBatch(10000), shader, ortho);

		GLSLProgram& shader2 = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		gui = new GUILayer(new SpriteBatch(10000), shader2, ortho);

		song = content->Load<Sound>("Akon.wav");
		sf = new SoundEffect3D(*song);
	}

	inline void Tick() override
	{
		std::cout << "FPS: " << m_FPS << std::endl;
	}

	inline void Update(float delta) override
	{
		layer->Update(delta);
		gui->Update(delta);

		if (Keyboard::IsKeyPressed(Keys::P))
		{
			sf->Play();
		}
	}

	inline void Render() override
	{
		layer->Render();
		gui->Render();
	}

	void Deinitialize() override
	{
		content->UnloadAll();
		delete sf;
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