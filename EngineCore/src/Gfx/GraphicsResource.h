#pragma once

namespace Shard
{
	namespace Gfx
	{
		class GraphicsResource
		{
		public:
			virtual ~GraphicsResource() { }

			virtual void Dispose() { }
		};
	}
}