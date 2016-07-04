#include "GUIButton.h"
#include "../Gfx/ColorUtils.h"
#include "../Input/Mouse.h"

namespace Shard
{
	namespace GUI
	{
		GUIButton::GUIButton(GUIComponent* parent, const Maths::Vector2f& pos, const Maths::Vector4f& color, GUILabel* label)
			: GUIContainer(parent, pos, label->GetSize()), m_Color(Gfx::ColorUtils::RGBATo32IntABGR(color)), m_Label(label), m_MousePosition(Input::Mouse::GetPosition()), m_MouseOver(false)
		{
			m_Padding = 10.0f;
			m_Size += Maths::Vector2f(2.0f * m_Padding, 2.0f * m_Padding);
			m_Transform = Maths::Matrix4f::Translation(m_Position + Maths::Vector3f(m_Padding, m_Padding, 0));
			AddComponent(m_Label);
		}

		GUIButton::GUIButton(const Maths::Vector2f& pos, const Maths::Vector4f& color, GUILabel* label)
			: GUIButton(nullptr, pos, color, label)
		{
		}
	}
}