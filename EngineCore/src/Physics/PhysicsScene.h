#pragma once

#include <vector>
#include "RigidBody.h"
#include "Mainfold.h"

namespace Shard
{
	namespace Physics
	{
		class PhysicsScene
		{
		private:
			std::vector<RigidBody*> m_Bodies;
			Maths::Vector2f m_Gravity;
			std::vector<Mainfold> m_Contacts;

		public:
			PhysicsScene(const Maths::Vector2f& grav);
			~PhysicsScene();

			void Update(float delta);
			RigidBody* Add(const Maths::Vector2f& pos, Shape* shape, const Material& mat);
		};
	}
}