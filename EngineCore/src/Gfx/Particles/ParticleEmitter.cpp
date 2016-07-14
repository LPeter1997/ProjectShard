#include "ParticleEmitter.h"
#include "../../Types.h"
#include "../Renderers/SpriteBatch.h"
#include "../ColorUtils.h"

namespace Shard
{
	namespace Gfx
	{
		ParticleEmitter::ParticleEmitter(const Maths::Vector2f& pos, float pps, float pspeed, float plife, Texture2D& tex)
			: m_Renderer(new SpriteBatch((uint)(pps * plife) + 1)), m_Position(pos), m_ParticlesPerSec(pps), m_ParticleSpeed(pspeed),
			m_ParticleLifeLength(plife), m_Leftover(0), m_ParticleTexture(tex)
		{
		}

		ParticleEmitter::~ParticleEmitter()
		{
			delete m_Renderer;
		}

		void ParticleEmitter::Update(float delta)
		{
			for (uint i = 0; i < m_Particles.size();)
			{
				Particle& p = m_Particles.at(i);
				p.Position += Maths::Vector2f(delta * p.Velocity.x, delta * p.Velocity.y);
				p.Life -= delta;
				if (p.Life <= 0)
					m_Particles.erase(m_Particles.begin() + i);
				else
					i++;
			}
			GenerateParticles(delta);
		}

		void ParticleEmitter::Render()
		{
			m_Renderer->Begin();
			for (const Particle& p : m_Particles)
			{
				m_Renderer->DrawTexture(Maths::Vector3f(p.Position.x, p.Position.y, 0),
					Maths::Vector2f(p.Scale * p.Texture.GetWidth(), p.Scale * p.Texture.GetHeight()),
					p.Rotation, p.Texture);
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
			float xspeed = ((float)std::rand() / (float)RAND_MAX - 0.5f);
			float yspeed = (float)std::rand() / (float)RAND_MAX - 0.5f;

			//float r = (float)std::rand() / (float)RAND_MAX;
			//float g = (float)std::rand() / (float)RAND_MAX;
			//float b = (float)std::rand() / (float)RAND_MAX;

			float s = (float)std::rand() / (float)RAND_MAX + 0.5f;

			Maths::Vector2f sp(xspeed, yspeed);
			sp.Normalize();
			sp = Maths::Vector2f(m_ParticleSpeed * sp.x, m_ParticleSpeed * sp.y);
			m_Particles.push_back(Particle(m_Position, sp, m_ParticleLifeLength, 0.0f, s, m_ParticleTexture));
		}
	}
}