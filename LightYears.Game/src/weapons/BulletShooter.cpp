#include "weapons/BulletShooter.h"
#include "framework/Core.h"
#include "weapons/projectiles/Bullet.h"
#include "framework/World.h"

namespace LightYear 
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime) 
		: Shooter{ owner },
		m_cooldownClock{ },
		m_cooldownTime{ cooldownTime }
	{

	}

	bool BulletShooter::IsOnCooldown() const
	{
		return (m_cooldownClock.getElapsedTime().asSeconds() < m_cooldownTime);
	}

	void BulletShooter::ShootAction()
	{
		m_cooldownClock.restart();
		auto texturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png";
		auto owner = GetOwner();
		Weak<Bullet> newBullet = owner->GetWorld()->SpawnActor<Bullet>(owner, texturePath);
		newBullet.lock()->SetLocation(owner->GetLocation());
		newBullet.lock()->SetRotation(owner->GetRotation());
	}
}