#include "GameStateManager.h"
#include "../Gfx/Window.h"
#include "../Input/Input.h"

namespace Shard
{
	namespace Logic
	{
		bool GameStateManager::s_Started = false;
		std::stack<GameState*> GameStateManager::s_StateStack;
		GameState* GameStateManager::s_CurrentState;
		Timer GameStateManager::s_Timer;

		void GameStateManager::Start()
		{
			if (s_Started)
				return;

			s_Started = true;
			Run();
		}

		void GameStateManager::PushState(GameState* state)
		{
			state->Initialize();
			s_StateStack.push(state);
			s_CurrentState = state;
		}

		void GameStateManager::ChangeState(GameState* state)
		{
			s_CurrentState->Deinitialize();
			s_StateStack.pop();
			state->Initialize();
			s_StateStack.push(state);
			s_CurrentState = state;
		}

		GameState* GameStateManager::PopState()
		{
			s_CurrentState->Deinitialize();
			GameState* st = s_CurrentState;
			s_StateStack.pop();
			s_CurrentState = s_StateStack.empty() ? nullptr : s_StateStack.top();
			return st;
		}

		void GameStateManager::Run()
		{
			uint frames = 0;
			float elapsed = 0.0f;
			Gfx::Window* disp = Gfx::Window::GetCurrent();
			
			s_Timer.Start();
			while (!disp->IsCloseRequested())
			{
				float delta = s_Timer.Reset();
				disp->Clear();
				s_CurrentState->Update(delta);
				s_CurrentState->Render();
				disp->Update();
				Input::InputDevices::Update();
				frames++;
				elapsed += delta;

				if (elapsed >= 1.0f)
				{
					s_CurrentState->m_FPS = frames;
					s_CurrentState->Tick();
					elapsed -= 1.0f;
					frames = 0;
				}
			}

			Stop();
		}

		void GameStateManager::Stop()
		{
			if (!s_Started)
				return;

			while (!s_StateStack.empty())
			{
				GameState* st = PopState();
				delete st;
			}

			s_Started = false;
		}
	}
}