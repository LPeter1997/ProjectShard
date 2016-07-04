#pragma once

#include <stack>
#include "..\Patterns\Static.h"
#include "GameState.h"
#include "Timer.h"

namespace Shard
{
	namespace Logic
	{
		class GameStateManager : public Patterns::Static
		{
		private:
			static bool s_Started;
			static std::stack<GameState*> s_StateStack;
			static GameState* s_CurrentState;
			static Timer s_Timer;

		public:
			static void Start();
			static void Stop();

			static void PushState(GameState* state);
			static void ChangeState(GameState* state);
			static GameState* PopState();

		private:
			static void Run();
		};
	}
}