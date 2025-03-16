#pragma once
#include "weapons/Shooter.h"
#include <SFML/System.hpp>

namespace LightYear 
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f);
		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootAction() override;

	private:
		sf::Clock m_cooldownClock;
		float m_cooldownTime;
	};
}