#pragma once

#include <vector>
#include "../Gfx/Renderers/Renderer2D.h"
#include "Transform.h"

namespace Shard
{
	namespace Components
	{
		class Component;

		class Actor
		{
		private:
			std::vector<Component*> m_Components;
			Transform m_Transform;

		public:
			Actor(const Maths::Vector3f& pos)
			{
				m_Transform.Position = pos;
			}

			~Actor()
			{
				for (Component* c : m_Components)
					delete c;
			}

			inline Transform& GetTransform() { return m_Transform; }

			inline void Render(Gfx::Renderer2D& renderer)
			{
				for (Component* c : m_Components)
					c->Render(renderer);
			}

			inline void Update(float delta)
			{
				for (Component* c : m_Components)
					c->Update(delta);
			}

			template <typename T>
			inline T* AddComponent()
			{
				T* c = new T(*this);
				m_Components.push_back(c);
				return c;
			}

			template <typename T>
			inline T* GetComponent()
			{
				for (Component* comp : m_Components)
				{
					T* c2 = dynamic_cast<T*>(comp);
					if (c2)
						return c2;
				}

				return nullptr;
			}

			template <typename T>
			inline std::vector<T*> GetComponents()
			{
				std::vector<T*> comps;

				for (Component* comp : m_Components)
				{
					T* c2 = dynamic_cast<T*>(comp);
					if (c2)
						comps.push_back(c2);
				}

				return comps;
			}
		};
	}
}