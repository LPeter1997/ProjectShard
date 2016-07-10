#include "AudioListener.h"

namespace Shard
{
	namespace Sfx
	{
		Maths::Vector3f AudioListener::m_Position = Maths::Vector3f();
		Maths::Vector3f AudioListener::m_Velocity = Maths::Vector3f();
		Maths::Orientationf AudioListener::m_Orientation = Maths::Orientationf();
	}
}