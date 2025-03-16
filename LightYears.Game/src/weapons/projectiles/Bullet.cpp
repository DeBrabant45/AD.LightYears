#include "weapons/projectiles/Bullet.h"

namespace LightYear
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{ world, texturePath },
		m_owner{ owner },
		m_speed{ speed },
		m_damage{ damage }
	{

	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetPhysics(true);
	}

	void Bullet::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void Bullet::SetDamage(float damage)
	{
		m_damage = damage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if (IsOutOfBounds())
		{
			Destroy();
		}
	}

	void Bullet::Move(float deltaTime)
	{
		AddLocationOffset(GetForwardDirection() * m_speed * deltaTime);
	}
}
