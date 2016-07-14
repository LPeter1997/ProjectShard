#include "ParticleEmitter.h"
#include "../../Types.h"
#include "../Renderers/SpriteBatch.h"

namespace Shard
{
	namespace Gfx
	{
		ParticleEmitter::ParticleEmitter(const Maths::Vector2f& pos, float pps, float pspeed, float plife)
			: m_Renderer(new SpriteBatch(5000)), m_Position(pos), m_ParticlesPerSec(pps), m_ParticleSpeed(pspeed), m_ParticleLifeLength(plife), m_Leftover(0)
		{
		}

		ParticleEmitter::~ParticleEmitter()
		{
			delete m_Renderer;
		}

		void ParticleEmitter::Update(float delta)
		{
			for (auto it = m_Particles.begin(); it != m_Particles.end();)
			{
				Particle& p = *it;
				p.Position += Maths::Vector2f(delta * p.Velocity.x, delta * p.Velocity.y);
				p.Life -= delta;
				if (p.Life <= 0)
					m_Particles.erase(it);
				else
					it++;
			}
			GenerateParticles(delta);
		}

		void ParticleEmitter::Render()
		{
			m_Renderer->Begin();
			for (Particle& p : m_Particles)
			{
				m_Renderer->DrawRectangle(Maths::Vector3f(p.Position.x, p.Position.y, 0), Maths::Vector2f(10, 10), 0xffffffff);
			}
			m_Renderer->End();
			m_Renderer->Render();
		}

		void ParticleEmitter::GenerateParticles(float delta)
		{
			float rc = delta * m_ParticlesPerSec + m_Leftover;
			uint toCreate = (uint)rc;
			
			for (uint i = 0; i < toCreate; i++)
				EmitParticle();

			m_Leftover = rc - (float)toCreate;
		}

		void ParticleEmitter::EmitParticle()
		{
			float xspeed = (float)std::rand() / (float)RAND_MAX - 0.5f;
			float yspeed = (float)std::rand() / (float)RAND_MAX - 0.5f;

			Maths::Vector2f sp(xspeed, yspeed);
			sp.Normalize();
			sp = Maths::Vector2f(m_ParticleSpeed * sp.x, m_ParticleSpeed * sp.y);
			m_Particles.push_back(Particle(m_Position, sp, m_ParticleLifeLength, 0.0f, 1.0f));
		}
	}
}