#include "PhysicsScene.h"
#include "NarrowPhase.h"
#include "ForceIntegrator.h"
#include "ImpulseIntegrator.h"

namespace Shard
{
	namespace Physics
	{
		PhysicsScene::PhysicsScene(const Maths::Vector2f& grav)
			: m_Gravity(grav)
		{
		}

		PhysicsScene::~PhysicsScene()
		{
			for (RigidBody* b : m_Bodies)
				delete b;
		}

		void PhysicsScene::Update(float delta)
		{
			m_Contacts.clear();

			// Get mainfolds
			for (uint i = 0; i < m_Bodies.size(); i++)
			{
				RigidBody* A = m_Bodies.at(i);

				for (uint j = i + 1; j < m_Bodies.size(); j++)
				{
					RigidBody* B = m_Bodies[j];
					if (A->BodyMass.InvMass == 0 && B->BodyMass.InvMass == 0)
						continue;

					Mainfold m(A, B);
					if (NarrowCollision::Collide(&m))
					{
						m_Contacts.push_back(m);
					}
				}
			}

			// Integrate forces
			for (uint i = 0; i < m_Bodies.size(); i++)
				ForceIntegrator::IntegrateForces(m_Bodies.at(i), m_Gravity, delta);

			// Initialize collisions
			for (uint i = 0; i < m_Contacts.size(); i++)
				m_Contacts.at(i).PreCompute(delta, m_Gravity);

			// Solve collisions
			for (uint i = 0; i < m_Contacts.size(); i++)
				ImpulseIntegrator::ApplyImpulse(&m_Contacts.at(i));

			// Integrate velocities
			for (uint i = 0; i < m_Bodies.size(); i++)
				ForceIntegrator::IntegrateVelocity(m_Bodies.at(i), m_Gravity, delta);

			// Correct positions
			for (uint i = 0; i < m_Contacts.size(); i++)
				ImpulseIntegrator::PositionalCorrection(&m_Contacts.at(i));

			// Clear forces
			for (uint i = 0; i < m_Bodies.size(); i++)
			{
				RigidBody* b = m_Bodies.at(i);
				b->Force.x = 0;
				b->Force.y = 0;
				b->Torque = 0;
			}
		}

		RigidBody* PhysicsScene::Add(const Maths::Vector2f& pos, Shape* shape, const Material& mat)
		{
			RigidBody* b = new RigidBody(pos, shape, mat);
			m_Bodies.push_back(b);
			return b;
		}
	}
}