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

public:
	TestState() {}

protected:
	void Initialize() override
	{
		content = new ContentManager("res");
		
		Text* file1 = content->Load<Text>("basic.vert");
		Text* file2 = content->Load<Text>("basic.frag");

		GLSLProgram& shader = ShaderFactory::CreateShader(file1->GetText(), file2->GetText());
		Matrix4f ortho = Matrix4f::Orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f);

		layer = new Layer2D(new SpriteBatch(10000), shader, ortho);
	}

	inline void Tick() override
	{
		std::cout << "FPS: " << m_FPS << std::endl;
	}

	inline void Update(float delta) override
	{
		layer->Update(delta);
	}

	inline void Render() override
	{
		layer->Render();
	}

	void Deinitialize() override
	{
		content->UnloadAll();
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