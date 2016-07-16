#include "ParticleArray.h"

namespace Shard
{
	namespace Gfx
	{
		ParticleArray::ParticleArray(uint max)
		{
			Generate(max);
		}

		ParticleArray::~ParticleArray()
		{
			delete[] Positions;
			delete[] Colors;
			delete[] StartColors;
			delete[] EndColors;
			delete[] Velocities;
			delete[] Accelerations;
			delete[] Times;
			delete[] Alives;
		}

		void ParticleArray::Generate(uint max)
		{
			m_Count = max;
			m_AliveCount = 0;

			Positions = new Maths::Vector4f[max];
			Colors = new Maths::Vector4f[max];
			StartColors = new Maths::Vector4f[max];
			EndColors = new Maths::Vector4f[max];
			Velocities = new Maths::Vector4f[max];
			Accelerations = new Maths::Vector4f[max];
			Times = new Maths::Vector4f[max];
			Alives = new bool[max];
		}

		void ParticleArray::Kill(uint idx)
		{
			Alives[idx] = false;
			Swap(idx, m_AliveCount - 1);
			m_AliveCount--;
		}

		void ParticleArray::Revive(uint idx)
		{
			Alives[idx] = true;
			//Swap(idx, m_AliveCount);
			m_AliveCount++;
		}

		void ParticleArray::Swap(uint a, uint b)
		{
			// Full swap not needed!
			/*std::swap(Positions[a], Positions[b]);
			std::swap(Colors[a], Colors[b]);
			std::swap(StartColors[a], StartColors[b]);
			std::swap(EndColors[a], EndColors[b]);
			std::swap(Velocities[a], Velocities[b]);
			std::swap(Accelerations[a], Accelerations[b]);
			std::swap(Times[a], Times[b]);
			std::swap(Alives[a], Alives[b]);*/
			Positions[a] = Positions[b];
			Colors[a] = Colors[b];
			StartColors[a] = StartColors[b];
			EndColors[a] = EndColors[b];
			Velocities[a] = Velocities[b];
			Accelerations[a] = Accelerations[b];
			Times[a] = Times[b];
			Alives[a] = Alives[b];
		}
	}
}