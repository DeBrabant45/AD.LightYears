#include "weapons/Shooter.h"

namespace LightYear
{
	Shooter::Shooter(Actor* owner) :
		m_owner{ owner }
	{

	}

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootAction();
		}
	}
}