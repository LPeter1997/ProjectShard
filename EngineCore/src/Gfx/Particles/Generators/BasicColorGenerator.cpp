#include "BasicColorGenerator.h"

namespace Shard
{
	namespace Gfx
	{
		namespace ParticleGenerators
		{
			void BasicColorGenerator::Generate(float delta, ParticleArray* particles, uint start, uint end)
			{
				Maths::Vector4f diffstart = MaxStartColor - MinStartColor;
				Maths::Vector4f diffend = MaxEndColor - MinEndColor;

				for (uint i = start; i < end; i++)
				{
					float at = (float)std::rand() / (float)RAND_MAX;
					float at2 = (float)std::rand() / (float)RAND_MAX;
					float at3 = (float)std::rand() / (float)RAND_MAX;
					float at4 = (float)std::rand() / (float)RAND_MAX;
					Maths::Vector4f col(at * diffstart.x + MinStartColor.x, at2 * diffstart.y + MinStartColor.y, at3 * diffstart.z + MinStartColor.z, at4 * diffstart.w + MinStartColor.w);
					particles->StartColors[i] = col;

					at = (float)std::rand() / (float)RAND_MAX;
					at2 = (float)std::rand() / (float)RAND_MAX;
					at3 = (float)std::rand() / (float)RAND_MAX;
					at4 = (float)std::rand() / (float)RAND_MAX;

					col = Maths::Vector4f(at * diffend.x + MinEndColor.x, at2 * diffend.y + MinEndColor.y, at3 * diffend.z + MinEndColor.z, at4 * diffend.w + MinEndColor.w);
					particles->EndColors[i] = col;
				}
			}
		}
	}
}