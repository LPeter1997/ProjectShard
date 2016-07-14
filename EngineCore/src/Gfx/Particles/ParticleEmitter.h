#pragma once

#include <vector>
#include "Particle.h"
#include "../Renderers/Renderer2D.h"

namespace Shard
{
	namespace Gfx
	{
		class ParticleEmitter
		{
		private:
			Renderer2D* m_Renderer;
			Maths::Vector2f m_Position;
			std::vector<Particle> m_Particles;
			float m_Leftover;
			// Emitted particle attribs
			float m_ParticlesPerSec;
			float m_ParticleSpeed;
			float m_ParticleLifeLength;

		public:
			ParticleEmitter(const Maths::Vector2f& pos, float pps, float pspeed, float plife);
			~ParticleEmitter();

			void Update(float delta);
			void Render();

		private:
			void GenerateParticles(float delta);
			void EmitParticle();
		};
	}
}