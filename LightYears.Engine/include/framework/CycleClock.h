#pragma once

#include <SFML/Graphics.hpp>

namespace LightYear
{
	class CycleClock
	{
	public:
		CycleClock(float cycleIterval);
		bool HasElapsed() const;
		void Reset();

	private:
		sf::Clock m_clock;
		float m_cycleIterval;
	};
}