#pragma once

#include "ParticleRenderer.h"
#include "../Buffers/VertexArray.h"

namespace Shard
{
	namespace Gfx
	{
		class BasicParticleRenderer : public ParticleRenderer
		{
		private:
			ParticleSystem* m_ParticleSystem;

			VertexArray* m_VAO;
			VertexBuffer* m_PositionBuffer;
			VertexBuffer* m_ColorBuffer;

		public:
			BasicParticleRenderer();
			~BasicParticleRenderer() { Destroy(); }

			void Generate(ParticleSystem* psys) override;
			void Destroy() override;
			void Update() override;
			void Render() override;
		};
	}
}