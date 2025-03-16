#include "framework/CycleClock.h"

namespace LightYear
{
	CycleClock::CycleClock(float cycleIterval) :
		m_cycleIterval { cycleIterval },
		m_clock { }
	{

	}

	bool CycleClock::HasElapsed() const
	{
		return m_clock.getElapsedTime().asSeconds() > m_cycleIterval;
	}

	void CycleClock::Reset()
	{
		m_clock.restart();
	}
}
