#pragma once

#include "../Types.h"

namespace Shard
{
	namespace Logic
	{
		class GameState
		{
		private:
			friend class GameStateManager;

		protected:
			uint m_FPS;

		public:
			GameState() {}

		protected:
			virtual void Initialize() {}
			virtual void Tick() {}
			virtual void Update(float delta) = 0;
			virtual void Render() = 0;
			virtual void Deinitialize() {}
		};
	}
}