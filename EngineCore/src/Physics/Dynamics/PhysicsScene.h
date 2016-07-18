#pragma once

#include <vector>
#include "RigidBody.h"
#include "../Collision/Mainfold.h"

namespace Shard
{
	namespace Physics
	{
		class PhysicsScene
		{
		private:
			std::vector<RigidBody*> m_Bodies;
			std::vector<Joint*> m_Joints;
			std::vector<Mainfold> m_Contacts;
			Maths::Vector2f m_Gravity;

		public:
			PhysicsScene(const Maths::Vector2f& grav);
			~PhysicsScene();

			void Update(float delta);
			RigidBody* AddRigidBody(const Maths::Vector2f& pos, Shape* shape, const Material& mat);
			void AddJoind(Joint* jnt);
		};
	}
}